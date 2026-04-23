# Trinity handbook integration notes

The handbook source is DocBook and is stored at:
- `en/index.docbook`

Typical TDE install destination is:
- `/usr/share/doc/tde/HTML/<lang>/tdeparted/index.docbook`

From this directory:
- Validate XML: `make validate`
- Build test HTML: `make html`
- Install handbook: `make install PREFIX=/usr`

Notes:
- The source was imported from `doc_en.txt`.
- Add missing image assets under `en/figures/` to satisfy all figure references.
