#!/usr/bin/env bash
set -euo pipefail

# ==============================================================================
# Script de mise à jour du Dépôt APT tdeParted & GitHub Pages
# ==============================================================================

REPO_DIR="$(cd "$(dirname "$0")" && pwd)"
DIST_DIR="$REPO_DIR/build/apt_repo"
PAGES_BRANCH="gh-pages"

need_cmd() {
    command -v "$1" >/dev/null 2>&1 || {
        echo "Error: missing required command: $1" >&2
        exit 1
    }
}

need_cmd dpkg-scanpackages
need_cmd apt-ftparchive
need_cmd git

echo "=================================================="
echo " tdeParted APT Repository & GitHub Pages Sync"
echo "=================================================="

# Ensure we have deb and qsi packages
DEB_FILES=($(find "$REPO_DIR" -maxdepth 1 -name "tdeparted_*_amd64.deb" | sort -V -r))
if [ ${#DEB_FILES[@]} -eq 0 ]; then
    echo "Error: No tdeparted_*_amd64.deb package found in $REPO_DIR." >&2
    echo "Please run ./build_deb.sh first." >&2
    exit 1
fi

QSI_FILES=($(find "$REPO_DIR" -maxdepth 1 -name "setup_tdeparted_*.qsi" | sort -V -r))

PAGES_DIR=$(mktemp -d -t tdeparted-gh-pages-XXXXXX)
echo "Staging in temporary directory: $PAGES_DIR"

REMOTE_URL="$(git -C "$REPO_DIR" remote get-url origin)"

# Clone or checkout gh-pages into temp directory
git clone --branch "$PAGES_BRANCH" --single-branch "$REMOTE_URL" "$PAGES_DIR" 2>/dev/null || {
    echo "Creating new orphan gh-pages branch in temp directory..."
    git init "$PAGES_DIR"
    (
        cd "$PAGES_DIR"
        git checkout --orphan "$PAGES_BRANCH"
        git remote add origin "$REMOTE_URL"
    )
}

# Structure pool and dists directories for standard APT repo
POOL_DIR="$PAGES_DIR/pool/main/t/tdeparted"
DISTS_DIR="$PAGES_DIR/dists/stable/main/binary-amd64"
mkdir -p "$POOL_DIR"
mkdir -p "$DISTS_DIR"

# Copy all deb packages into pool
for deb in "${DEB_FILES[@]}"; do
    echo "  -> Added DEB: $(basename "$deb")"
    cp -a "$deb" "$POOL_DIR/"
done

# Copy latest QSI to root of pages
for qsi in "${QSI_FILES[@]}"; do
    echo "  -> Added QSI: $(basename "$qsi")"
    cp -a "$qsi" "$PAGES_DIR/"
done

# Generate Packages & Packages.gz index files
echo "Generating Packages index..."
(
    cd "$PAGES_DIR"
    dpkg-scanpackages --multiversion --arch amd64 pool/main > "$DISTS_DIR/Packages"
    gzip -9 -c "$DISTS_DIR/Packages" > "$DISTS_DIR/Packages.gz"
)

# Generate Release file
echo "Generating Release manifest..."
apt-ftparchive \
  -o APT::FTPArchive::Release::Origin="tdeparted" \
  -o APT::FTPArchive::Release::Label="tdeParted APT Repository" \
  -o APT::FTPArchive::Release::Suite="stable" \
  -o APT::FTPArchive::Release::Codename="stable" \
  -o APT::FTPArchive::Release::Architectures="amd64" \
  -o APT::FTPArchive::Release::Components="main" \
  -o APT::FTPArchive::Release::Description="APT Repository for tdeParted (Trinity Desktop & Linux - based on GParted)" \
  release "$PAGES_DIR/dists/stable" > "$PAGES_DIR/dists/stable/Release"

# Copy assets (about image, favicon, icons, screenshots)
if [ -f "$REPO_DIR/icons/tdeparted_about.png" ]; then
    cp -a "$REPO_DIR/icons/tdeparted_about.png" "$PAGES_DIR/tdeparted_about.png"
fi
if [ -f "$REPO_DIR/icons/tdeparted_icon.png" ]; then
    cp -a "$REPO_DIR/icons/tdeparted_icon.png" "$PAGES_DIR/favicon.png"
    cp -a "$REPO_DIR/icons/tdeparted_icon.png" "$PAGES_DIR/tdeparted_icon.png"
fi
if [ -d "$REPO_DIR/icons" ]; then
    cp -a "$REPO_DIR/icons" "$PAGES_DIR/"
fi
if [ -d "$REPO_DIR/screenshots" ]; then
    cp -a "$REPO_DIR/screenshots" "$PAGES_DIR/"
fi

# Create .nojekyll to prevent GitHub Pages Jekyll processing
touch "$PAGES_DIR/.nojekyll"

# Find latest file names and version for HTML
LATEST_VERSION=$(dpkg-deb -f "${DEB_FILES[0]}" Version 2>/dev/null || echo "1.0")
LATEST_DEB_NAME=$(basename "${DEB_FILES[0]}")
LATEST_QSI_NAME=""
if [ ${#QSI_FILES[@]} -gt 0 ]; then
    LATEST_QSI_NAME=$(basename "${QSI_FILES[0]}")
fi

cat << EOF > "$PAGES_DIR/index.html"
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>tdeParted v${LATEST_VERSION} - APT Repository (based on GParted)</title>
  <link rel="icon" type="image/png" href="favicon.png">
  <meta name="description" content="Official APT Repository and download portal for tdeParted - Advanced Partition Editor for Trinity Desktop Environment (TDE) & Linux based on GParted, with several additional exclusive features.">
  <style>
    :root {
      --bg: #12141a;
      --card-bg: #1c1f2b;
      --card-hover: #222738;
      --accent: #38bdf8;
      --accent-grad: linear-gradient(135deg, #0284c7, #38bdf8);
      --text: #e2e8f0;
      --text-muted: #94a3b8;
      --code-bg: #0f1117;
      --border: #2e364f;
      --radius: 12px;
      --radius-sm: 8px;
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    body {
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
      background-color: var(--bg);
      color: var(--text);
      line-height: 1.6;
      padding: 40px 20px;
    }

    .container {
      max-width: 840px;
      margin: 0 auto;
    }

    header {
      text-align: center;
      margin-bottom: 40px;
    }

    .logo {
      max-height: 120px;
      width: auto;
      margin-bottom: 16px;
      filter: drop-shadow(0 8px 24px rgba(56, 189, 248, 0.4));
      border-radius: 18px;
      transition: transform 0.3s cubic-bezier(0.34, 1.56, 0.64, 1);
    }

    .logo:hover {
      transform: scale(1.08) rotate(3deg);
    }

    .badge-group {
      display: flex;
      justify-content: center;
      gap: 10px;
      margin-bottom: 12px;
      flex-wrap: wrap;
    }

    .badge {
      display: inline-block;
      padding: 4px 14px;
      font-size: 0.85rem;
      font-weight: 600;
      color: #fff;
      background: var(--accent-grad);
      border-radius: 20px;
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }

    .badge-green {
      background: linear-gradient(135deg, #15803d, #22c55e);
    }

    .badge-purple {
      background: linear-gradient(135deg, #6366f1, #a855f7);
    }

    .version-pill {
      display: inline-block;
      font-size: 1.1rem;
      font-weight: 600;
      color: #38bdf8;
      background: rgba(56, 189, 248, 0.12);
      border: 1px solid rgba(56, 189, 248, 0.35);
      padding: 2px 12px;
      border-radius: 20px;
      vertical-align: middle;
      margin-left: 8px;
    }

    h1 {
      font-size: 2.4rem;
      font-weight: 700;
      margin-bottom: 8px;
      display: flex;
      align-items: center;
      justify-content: center;
    }

    p.lead {
      font-size: 1.1rem;
      color: var(--text-muted);
      max-width: 680px;
      margin: 0 auto;
    }

    .card {
      background: var(--card-bg);
      border: 1px solid var(--border);
      border-radius: var(--radius);
      padding: 24px;
      margin-bottom: 24px;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.3);
    }

    h2 {
      font-size: 1.3rem;
      margin-bottom: 14px;
      display: flex;
      align-items: center;
      gap: 10px;
      color: #fff;
    }

    /* Terminal & Code snippet box */
    .code-container {
      position: relative;
      margin-top: 10px;
    }

    pre {
      background: var(--code-bg);
      border: 1px solid var(--border);
      border-radius: var(--radius-sm);
      padding: 16px;
      padding-right: 80px;
      overflow-x: auto;
      font-family: "Courier New", Courier, monospace;
      font-size: 0.92rem;
      color: #38bdf8;
      line-height: 1.6;
    }

    .copy-btn {
      position: absolute;
      top: 12px;
      right: 12px;
      background: rgba(255, 255, 255, 0.08);
      border: 1px solid rgba(255, 255, 255, 0.18);
      color: var(--text);
      padding: 5px 12px;
      border-radius: 6px;
      font-size: 0.8rem;
      cursor: pointer;
      transition: all 0.2s;
    }

    .copy-btn:hover {
      background: var(--accent);
      color: #fff;
      border-color: var(--accent);
    }

    /* Downloads Grid */
    .downloads-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
      gap: 16px;
      margin-top: 16px;
    }

    .download-card {
      background: #141722;
      border: 1px solid var(--border);
      border-radius: var(--radius-sm);
      padding: 18px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      transition: all 0.2s ease;
    }

    .download-card:hover {
      transform: translateY(-2px);
      border-color: #38bdf8;
      background: var(--card-hover);
    }

    .download-header {
      display: flex;
      align-items: center;
      justify-content: space-between;
      margin-bottom: 8px;
    }

    .download-title {
      font-size: 1.05rem;
      font-weight: 700;
      color: #fff;
    }

    .download-tag {
      font-size: 0.72rem;
      font-weight: 600;
      padding: 2px 8px;
      border-radius: 12px;
      background: rgba(56, 189, 248, 0.15);
      color: #38bdf8;
      border: 1px solid rgba(56, 189, 248, 0.3);
    }

    .download-desc {
      font-size: 0.85rem;
      color: var(--text-muted);
      margin-bottom: 14px;
      flex-grow: 1;
    }

    .btn-download {
      background: #1e293b;
      color: #38bdf8;
      border: 1px solid #334155;
      padding: 8px 14px;
      border-radius: 6px;
      text-align: center;
      text-decoration: none;
      font-weight: 600;
      font-size: 0.9rem;
      transition: all 0.2s;
    }

    .btn-download:hover {
      background: var(--accent);
      color: #ffffff;
      border-color: var(--accent);
    }

    .features-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
      gap: 16px;
      margin-top: 14px;
    }

    .feature-item {
      background: #141722;
      border: 1px solid var(--border);
      border-radius: var(--radius-sm);
      padding: 16px;
    }

    .feature-icon {
      font-size: 1.4rem;
      margin-bottom: 6px;
      display: inline-block;
    }

    .feature-title {
      font-size: 0.98rem;
      font-weight: 700;
      color: #ffffff;
      margin-bottom: 4px;
    }

    .feature-text {
      font-size: 0.85rem;
      color: var(--text-muted);
      line-height: 1.45;
    }

    /* Screenshots gallery */
    .screenshots-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
      gap: 12px;
      margin-top: 14px;
    }

    .screenshot-thumb {
      border-radius: var(--radius-sm);
      overflow: hidden;
      border: 1px solid var(--border);
      cursor: pointer;
      aspect-ratio: 16 / 10;
      background: #0f1117;
      transition: all 0.2s ease;
      position: relative;
    }

    .screenshot-thumb:hover {
      transform: scale(1.03);
      border-color: #38bdf8;
      box-shadow: 0 6px 20px rgba(56, 189, 248, 0.25);
    }

    .screenshot-thumb img {
      width: 100%;
      height: 100%;
      object-fit: cover;
      display: block;
    }

    .screenshot-label {
      position: absolute;
      bottom: 0;
      left: 0;
      right: 0;
      background: rgba(15, 17, 23, 0.85);
      backdrop-filter: blur(4px);
      padding: 4px 8px;
      font-size: 0.75rem;
      color: #e2e8f0;
      text-align: center;
      border-top: 1px solid rgba(255, 255, 255, 0.08);
    }

    /* Modal / Lightbox */
    .modal {
      display: none;
      position: fixed;
      z-index: 1000;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: rgba(0, 0, 0, 0.88);
      backdrop-filter: blur(6px);
      align-items: center;
      justify-content: center;
      padding: 20px;
    }

    .modal.active {
      display: flex;
    }

    .modal-content {
      display: flex;
      flex-direction: column;
      align-items: center;
      max-width: 92vw;
      max-height: 90vh;
    }

    .modal img {
      max-width: 90vw;
      max-height: 84vh;
      border-radius: 8px;
      border: 1px solid var(--border);
      box-shadow: 0 12px 40px rgba(0, 0, 0, 0.6);
      object-fit: contain;
    }

    .modal-caption {
      margin-top: 10px;
      color: #94a3b8;
      font-size: 0.9rem;
    }

    .modal-close {
      position: absolute;
      top: 20px;
      right: 30px;
      font-size: 2.2rem;
      color: #fff;
      cursor: pointer;
      line-height: 1;
    }

    footer {
      text-align: center;
      margin-top: 45px;
      font-size: 0.9rem;
      color: var(--text-muted);
    }

    footer a {
      color: var(--accent);
      text-decoration: none;
    }

    footer a:hover {
      text-decoration: underline;
    }

    .footer-links {
      margin-top: 8px;
      font-size: 0.82rem;
      color: #64748b;
    }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <img src="tdeparted_about.png" alt="tdeParted Logo" class="logo">
      <div class="badge-group">
        <div class="badge">Official APT Repository</div>
        <div class="badge badge-green">TDE &amp; Linux Native</div>
        <div class="badge">x86_64</div>
      </div>
      <h1>tdeParted <span class="version-pill">v${LATEST_VERSION}</span></h1>
      <p class="lead">Advanced Partition Editor for Trinity Desktop Environment (TDE) &amp; Linux based on GParted, with several additional exclusive features.</p>
    </header>

    <!-- Method 1: APT Repository -->
    <div class="card">
      <h2>
        <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><path d="M4 17l6-6-6-6M12 19h8"/></svg>
        Method 1: Add the APT Repository (Recommended)
      </h2>
      <p style="color: var(--text-muted); font-size: 0.95rem;">
        Add the official repository to your system to receive regular automated updates via <code>apt</code>:
      </p>

      <div class="code-container">
        <pre id="apt-code"><code>echo "deb [trusted=yes] https://seb3773.github.io/tdeparted/ stable main" | sudo tee /etc/apt/sources.list.d/tdeparted.list
sudo apt update
sudo apt install tdeparted</code></pre>
        <button class="copy-btn" onclick="copyCode('apt-code', this)">Copy</button>
      </div>

      <p style="color: var(--text-muted); font-size: 0.85rem; margin-top: 14px;">
        Compatible with Q4OS, Debian, Devuan, Ubuntu, Linux Mint and all Debian-based distributions.
      </p>
    </div>

    <!-- Method 2: Direct Packages -->
    <div class="card">
      <h2>
        <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4M7 10l5 5 5-5M12 15V3"/></svg>
        Method 2: Direct Package Download (.deb / .qsi)
      </h2>
      <p style="color: var(--text-muted); font-size: 0.95rem;">
        Choose the package format best suited for your distribution:
      </p>

      <div class="downloads-grid">
        <div class="download-card">
          <div class="download-header">
            <span class="download-title">Debian / TDE (.deb)</span>
            <span class="download-tag">Recommended</span>
          </div>
          <p class="download-desc">Standard dynamically linked build for Trinity Desktop / Debian-based systems.</p>
          <a href="pool/main/t/tdeparted/${LATEST_DEB_NAME}" class="btn-download">
            Download .deb
          </a>
        </div>

        <div class="download-card">
          <div class="download-header">
            <span class="download-title">Q4OS Installer (.qsi)</span>
            <span class="download-tag">Q4OS 1-Click</span>
          </div>
          <p class="download-desc">Graphical one-click installer designed specifically for Q4OS Trinity desktop.</p>
          <a href="${LATEST_QSI_NAME}" class="btn-download">
            Download .qsi
          </a>
        </div>
      </div>
      <p style="color: var(--text-muted); font-size: 0.85rem; margin-top: 16px;">
        * Note: The Q4OS installer (.qsi) automatically configures the APT repository during installation for future updates.
      </p>
    </div>

    <!-- Key Features -->
    <div class="card">
      <h2>
        <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><path d="M13 2L3 14h9l-1 8 10-12h-9l1-8z"/></svg>
        Key Capabilities &amp; Architecture
      </h2>

      <div class="features-grid">
        <div class="feature-item">
          <span class="feature-icon">🚀</span>
          <div class="feature-title">Native TQt3 / C++ Performance</div>
          <div class="feature-text">Starts instantly, consumes only a few megabytes of RAM, and seamlessly integrates with Trinity Desktop Environment (TDE).</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">💾</span>
          <div class="feature-title">Partition Management</div>
          <div class="feature-text">Create, delete, resize, move, copy, paste, check partitions, and manage partition flags with safety checks.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">🔒</span>
          <div class="feature-title">Secure Disk Erase</div>
          <div class="feature-text">Securely sanitize and erase whole storage devices with multiple zeroing and pattern algorithms.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">🩺</span>
          <div class="feature-title">S.M.A.R.T. Health Monitor</div>
          <div class="feature-text">Diagnostic health overview, temperature monitoring, and attribute inspection for NVMe, SSD, and HDD drives.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">⚡</span>
          <div class="feature-title">Quick Benchmark</div>
          <div class="feature-text">Fast integrated read and write throughput testing to evaluate drive performance directly in the UI.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">📦</span>
          <div class="feature-title">Disk &amp; Partition Imaging</div>
          <div class="feature-text">Create and restore raw partition or entire disk image backups seamlessly.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">👥</span>
          <div class="feature-title">Device Cloning &amp; Expand</div>
          <div class="feature-text">Direct whole device-to-device cloning with optional automatic partition expansion on target disk.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">📜</span>
          <div class="feature-title">Export Pending Operations</div>
          <div class="feature-text">Export any queued sequence of partition operations directly into an executable standalone bash script.</div>
        </div>

        <div class="feature-item">
          <span class="feature-icon">🔄</span>
          <div class="feature-title">MBR / GPT Table Conversion</div>
          <div class="feature-text">Create new partition tables or convert between MBR and GPT with automated safety backups in /var/tmp/.</div>
        </div>
      </div>
    </div>

    <!-- Screenshots -->
    <div class="card">
      <h2>
        <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><rect x="3" y="3" width="18" height="18" rx="2" ry="2"/><circle cx="8.5" cy="8.5" r="1.5"/><polyline points="21 15 16 10 5 21"/></svg>
        Screenshots
      </h2>
      <div class="screenshots-grid">
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_1.jpg', 'Main Partition View')">
          <img src="screenshots/screenshot_1.jpg" alt="Main Partition View">
          <div class="screenshot-label">Main Partition View</div>
        </div>
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_2.jpg', 'Partition Operations')">
          <img src="screenshots/screenshot_2.jpg" alt="Partition Operations">
          <div class="screenshot-label">Partition Operations</div>
        </div>
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_3.jpg', 'S.M.A.R.T. Diagnostics')">
          <img src="screenshots/screenshot_3.jpg" alt="S.M.A.R.T. Diagnostics">
          <div class="screenshot-label">S.M.A.R.T. Diagnostics</div>
        </div>
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_4.jpg', 'Disk Benchmark')">
          <img src="screenshots/screenshot_4.jpg" alt="Disk Benchmark">
          <div class="screenshot-label">Disk Benchmark</div>
        </div>
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_5.jpg', 'Secure Disk Erase')">
          <img src="screenshots/screenshot_5.jpg" alt="Secure Disk Erase">
          <div class="screenshot-label">Secure Disk Erase</div>
        </div>
        <div class="screenshot-thumb" onclick="openModal('screenshots/screenshot_6.jpg', 'Disk Imaging &amp; Cloning')">
          <img src="screenshots/screenshot_6.jpg" alt="Disk Imaging &amp; Cloning">
          <div class="screenshot-label">Imaging &amp; Cloning</div>
        </div>
      </div>
    </div>

    <!-- Footer -->
    <footer>
      <p>Source Code &amp; Releases: <a href="https://github.com/seb3773/tdeparted" target="_blank" rel="noopener">github.com/seb3773/tdeparted</a></p>
      <p style="margin-top: 6px;">tdeParted is based on <a href="https://github.com/GNOME/gparted" target="_blank" rel="noopener">GNOME GParted</a>. Developed with ❤️ for the Trinity Desktop Environment community.</p>
      <p class="footer-links">
        <a href="http://trinitydesktop.org/" target="_blank" rel="noopener">http://trinitydesktop.org/</a> &bull; 
        <a href="https://www.q4os.org/" target="_blank" rel="noopener">https://www.q4os.org/</a> &bull; 
        <a href="https://www.q4os.org/forum/index.php" target="_blank" rel="noopener">https://www.q4os.org/forum/index.php</a>
      </p>
    </footer>

  </div>

  <!-- Lightbox Modal -->
  <div id="imageModal" class="modal" onclick="closeModal()">
    <span class="modal-close">&times;</span>
    <div class="modal-content" onclick="event.stopPropagation()">
      <img id="modalImg" src="" alt="Enlarged screenshot">
      <div id="modalCaption" class="modal-caption"></div>
    </div>
  </div>

  <script>
    function copyCode(id, btn) {
      const text = document.getElementById(id).innerText;
      navigator.clipboard.writeText(text).then(() => {
        const orig = btn.innerText;
        btn.innerText = "Copied!";
        setTimeout(() => btn.innerText = orig, 2000);
      });
    }

    function openModal(src, caption) {
      document.getElementById('modalImg').src = src;
      document.getElementById('modalCaption').innerText = caption || '';
      document.getElementById('imageModal').classList.add('active');
    }

    function closeModal() {
      document.getElementById('imageModal').classList.remove('active');
    }

    document.addEventListener('keydown', (e) => {
      if (e.key === 'Escape') closeModal();
    });
  </script>
</body>
</html>
EOF

# Copy index.html to local repo as well (for main branch tracking)
cp -a "$PAGES_DIR/index.html" "$REPO_DIR/index.html"

# Git commit and push to gh-pages
echo "Committing and pushing to gh-pages branch..."
(
    cd "$PAGES_DIR"
    git add -A
    git commit -m "Update APT repository and portal page: $(date +'%Y-%m-%d %H:%M:%S')" || echo "No changes to commit."
    git push origin "$PAGES_BRANCH"
)

echo "Cleaning up temporary directory..."
rm -rf "$PAGES_DIR"

echo "=================================================="
echo " SUCCESS: APT repository updated on gh-pages!"
echo " URL: https://seb3773.github.io/tdeparted/"
echo "=================================================="
