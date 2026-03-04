# MultithreadDataAnalysis
Multithreaded C program that analyzes Spotify CSV data using 8 worker threads. Each thread processes a chunk of rows, computing sum, min, and max for all numeric fields (e.g., popularity, energy, tempo). Threads write to isolated argument structs to avoid conflicts; the main thread aggregates final results and logs per-field stats.
