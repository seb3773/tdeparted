# tdeParted
![tdeParted](./konqi/konqi_parted.jpg)
## A Partition Editor for Trinity Desktop

tdeParted is based on GParted (https://github.com/GNOME/gparted). Originally intended as a TQt3 port of GParted, several features not present in GParted have been added. These include a secure erase function, a summary of S.M.A.R.T. information for compatible devices, a quick benchmark to get an idea of a drive’s read and write performance (not a replacement for dedicated disk benchmarking tools, but useful for a quick estimate), creation and restoration of disk/partition images, device cloning, the ability to export a pending operation chain as a bash script, copy-to-clipboard support in key dialogs, and a graphical overhaul with improved ergonomics (a more complete toolbar, quick mount/unmount buttons for partitions, and other details).
A big thank you to the authors of GParted, without whom this tool would obviously not exist.

This repository targets **TDE only**.

## Scope

- **Desktop**
  Trinity Desktop Environment (TDE) / TQt3.
- **Platform**
  Linux.
- **Privileges**
  Requires elevated privileges to perform operations on block devices.

## Features

- **Partition management**
  Create, delete, resize, move, copy, paste, check partitions, and manage partition flags.
- **Secure erase**
  Securely erase a whole disk device.
- **S.M.A.R.T. summary**
  Display a summary of S.M.A.R.T. information for compatible drives.
- **Quick benchmark**
  Quick estimate of read/write performance.
- **Disk / partition imaging**
  Create and restore disk or partition images.
- **Device cloning**
  Clone a whole disk device to another one (requires an unused target device of equal or larger size). Optionally expand a partition after cloning in safe cases.
- **Export pending operations**
  Export the current pending operation chain as a bash script.
- **Create / convert partition tables as pending operations**
  Create a new partition table (MBR/GPT) or convert between MBR and GPT as a queued operation, executed only when applying pending operations. GPT to MBR conversion uses `sgdisk` and is limited to up to 4 partitions. A GPT backup is created under `/var/tmp/` before conversion.
- **Copy to clipboard**
  Copy textual reports from key dialogs (such as operation reports and device/partition information).

## Install

### Debian package

If you build the package with `./build_deb.sh`, the resulting file is created in the project root.

Install with:

```sh
sudo dpkg -i ./tdeparted_*.deb
```

## Build

This project uses Autotools.

### Dependencies

You need a working Trinity/TQt3 development environment and a working libparted development setup.

### Quick build (from project root)

```sh
./configure
make -j$(nproc)
```

### Convenience scripts

- `./build.sh`
  Automatic out-of-tree build into `./build/` (runs `autogen.sh` and `configure` when needed).
- `./build_deb.sh`
  Builds a release binary and produces a `.deb` package (also builds out-of-tree into `./build/`).

### After editing sources in src/

The reliable way to rebuild the executable is to build the target directly in `src/`:

```sh
make tdepartedbin
```

(Run from the `src/` directory.) This forces recompilation/relink of the actual executable even when the top-level `make` may report "nothing to be done".

If you need to force a full relink after editing `Win_GParted_TQt.cc`:

```sh
rm -f Win_GParted_TQt.o moc_Win_GParted_TQt.o tdepartedbin
make tdepartedbin
```

### If config.status is missing

```sh
./configure
```

Or, if `configure` was already run and you only need to regenerate Makefiles:

```sh
./config.status
```

### Clean rebuild

```sh
make clean
make -j$(nproc)
```

### Very clean rebuild

```sh
make distclean
./configure
make -j$(nproc)
```

### Configure flags

If you wish to build this package to use native libparted `/dev/mapper` dmraid support use the `--enable-libparted-dmraid` flag:

```sh
./configure --enable-libparted-dmraid
```

## Runtime

`tdeParted` requires root privileges to operate on block devices.

Depending on your setup, this is typically achieved via polkit/pkexec.

## Documentation

The Trinity handbook (DocBook) lives under `doc/` and is installed under:

`/usr/share/doc/tde/HTML/<lang>/tdeparted/index.docbook`

The application menu opens the handbook via:

`tdehelpcenter help:/tdeparted`

To generate a local HTML file for review (no install), from `doc/`:

```sh
make html
```

The resulting file is:

`doc/build/en/index.html`

## Licensing

- Code: GPLv2+ (see `COPYING`)
- Documentation: GFDLv1.2+ (see `COPYING-DOCS`)

## Upstream

- GParted upstream project: https://gparted.org

## Repository notes

The legacy upstream README of gparted is kept as a reference in `upstream/README.gparted`.
