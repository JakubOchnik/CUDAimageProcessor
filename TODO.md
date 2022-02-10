# List of basic things to do
1. Rewrite GPU memory pipeline (use unified memory)
    - mostly done (functions correctly)
    - only crop/resize not working
2. Find an efficient way to distinguish between GPU and CPU commands (different MainHandlers for GPU and CPU)
    - needs to be done in order to finish 1)
3. Handle GPU memory in undo/redo commands