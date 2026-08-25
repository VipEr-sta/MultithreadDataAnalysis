# Multithreaded Spotify Data Analysis

An educational C project that explores parallel data processing with POSIX threads. The program loads Spotify track data from a CSV file, distributes numeric-field summation across eight worker threads, joins the workers, and reduces their partial results on the main thread.

The project was built as an Operating Systems course project to practice thread creation, work partitioning, shared-memory design, and result aggregation in C.

## What This Project Demonstrates

- Creating and joining multiple workers with `pthread_create` and `pthread_join`
- Dividing row ranges among eight threads
- Sharing a read-only dataset while giving each thread isolated result storage
- Aggregating per-thread partial sums after all workers complete
- Parsing mixed text and numeric CSV columns into C structures
- Calculating minimum and maximum values in a separate main-thread pass
- Organizing a C project with headers, source files, and CMake

## Processing Flow

1. `Main.c` opens the Spotify CSV and skips its header row.
2. Each record is parsed into a `musicRow` structure containing five text fields and eleven numeric fields.
3. Eight `SpotArgs` structures define the row range and private result arrays assigned to each worker.
4. `Chunk_Thread` traverses its half-open range, `[startIndex, endIndex)`, and accumulates a partial sum for every numeric column.
5. The main thread waits for all eight workers and combines their partial sums.
6. Minimum and maximum values are calculated afterward by the main thread.

Because each worker writes only to its own `SpotArgs.sum` array, the parallel summation does not require a shared accumulator or locking.

## Dataset

The bundled `spotify_analysis_dataset.csv` contains 50 sample tracks.

| Category | Columns |
| --- | --- |
| Text | `track_id`, `track_name`, `artist`, `album`, `release_date` |
| Numeric | `duration_ms`, `popularity`, `danceability`, `energy`, `loudness`, `speechiness`, `acousticness`, `instrumentalness`, `liveness`, `valence`, `tempo` |

The in-memory row buffer currently supports up to 1,000 records.

## Project Structure

```text
.
├── Main.c                        # CSV loading, thread orchestration, and final reduction
├── Worker.c                      # Worker-thread summation routine
├── Worker.h                      # Row and thread-argument structures
├── Statistics.c                  # Experimental combined-statistics routine
├── Statistics.h                  # Numeric-field count and statistics declaration
├── spotify_analysis_dataset.csv  # Sample input data
└── CMakeLists.txt                # C11 build configuration and thread linkage
```

## Requirements

The current implementation targets a Windows development environment.

- A C11 compiler
- CMake 4.0 or newer, as configured in `CMakeLists.txt`
- A pthreads implementation discoverable by CMake
- Windows-compatible headers for `_getcwd` and `<direct.h>`

The source was developed in CLion. Linux and macOS require small portability changes described below.

## Build and Run

### 1. Clone the repository

```bash
git clone https://github.com/VipEr-sta/MultithreadDataAnalysis.git
cd MultithreadDataAnalysis
```

### 2. Configure the dataset path

`Main.c` currently opens the CSV using an absolute Windows path. Change that value to the location of `spotify_analysis_dataset.csv` on your machine.

For example, when the CSV is in the program's working directory:

```c
FILE *spotifyFile = fopen("spotify_analysis_dataset.csv", "r");
```

### 3. Configure and build

```bash
cmake -S . -B build
cmake --build build
```

### 4. Run

Run the generated `Multithread_Parallel_Data_Analysis` executable from your build output directory. Make sure the configured CSV path is valid for that working directory.

## Program Output

The program prints:

- The current working directory and CSV-loading status
- Each parsed CSV row
- The range handled by each worker thread
- Aggregated sums for the numeric fields
- Minimum and maximum values calculated by the main thread

Thread-status messages may appear in a different order between executions. That is expected because thread scheduling is nondeterministic.

## Current Prototype Constraints

This repository captures the course-project implementation rather than a production-ready data engine. Its current constraints are:

- Thread ranges and `totalRows` are manually configured for a subset of the loaded records instead of being generated from the actual row count.
- The current range map should be recalculated before using the full bundled dataset.
- Only summation is performed in parallel; minimum and maximum calculations run sequentially.
- CSV parsing uses `strtok`, so quoted fields containing commas are not supported.
- The input path is hard-coded for the original Windows development environment.
- `<direct.h>` and `_getcwd` are Windows-specific.
- `Statistics.h` references `worker.h`, while the repository file is named `Worker.h`; this matters on case-sensitive file systems.
- The printed field-label array should be aligned with all eleven numeric CSV columns before its labels are treated as authoritative.
- The row buffer has a fixed capacity of 1,000 records.

## Possible Improvements

- Determine the loaded row count dynamically and generate balanced worker ranges
- Parallelize sum, minimum, maximum, and average as a single reduction
- Replace the absolute file path with a command-line argument
- Add a quote-aware CSV parser and input validation
- Make path and header handling portable across Windows, Linux, and macOS
- Add timing measurements to compare sequential and multithreaded execution
- Add automated tests for parsing, range coverage, and aggregate correctness

## Key Takeaway

The central design idea is simple: workers share the input rows for reading, keep their intermediate results isolated, and synchronize only when the main thread joins them and performs the final reduction. That pattern is a foundation for larger parallel-processing systems.
