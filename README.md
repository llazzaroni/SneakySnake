# SneakySnake: A Fast and Accurate Universal Genome Pre-Alignment Filter

## Overview

SneakySnake is a high-performance algorithm designed to accelerate the genome sequencing process by providing a fast and efficient pre-alignment filtering technique. It reduces the computational cost associated with sequence alignment by addressing the Sequence-Number Ratio (SNR) problem and offering a low-cost solution to identify incorrect candidate locations in genomic sequences. This repository contains multiple implementations of the algorithm, each optimized for different runtime and memory performance.

The project was developed as part of the P&S Genome Sequencing on Mobile Devices course at ETH Zurich (HS2022).

## Algorithm Overview

SneakySnake accelerates genome sequence alignment by filtering out most incorrect mapping locations with minimal computation, thereby reducing the workload for later, more expensive sequence alignment stages. The core of the SneakySnake algorithm is based on the concept of reducing the Approximate String Matching (ASM) problem to the Single Net Routing (SNR) problem.

### How SneakySnake Works

1. Sequence Comparison: The algorithm compares a read from the genome to a reference genome by shifting the read across the reference and computing the length of matching subsequences at each offset.
2. Obstacle Detection: If mismatches (obstacles) are found, the algorithm increments the edit distance and repeats the matching process until the total distance is calculated.
3. Efficient Filtering: Once the desired maximal edit distance is reached, the algorithm stops, and the comparison result is output. This pre-alignment filtering step is computationally cheaper than full sequence alignment, enabling faster analysis.

## Key Implementations

### 1. Standard SneakySnake

- Compares two strings character by character, shifting the read across the reference genome.
- Outputs the edit distance based on the longest matching subsequence.
  
### 2. SneakySnakeMat (Matrix-Based Version)

- Precomputes a matrix that stores all character comparisons between the read and reference genome.
- Slower than the standard version due to matrix precomputation, but optimizes repeated calculations.

### 3. SneakySnakeMat with Hashing

- Optimizes the matrix-based approach by hashing substrings of the reference genome and the read, reducing the matrix size and improving runtime.
- Hashes substrings of varying lengths to find the optimal balance between runtime and accuracy.

## Performance and Comparisons

### Runtime Comparison

To assess the performance of each implementation, runtimes were measured using 30,000 pairs of 100-character strings. The standard SneakySnake algorithm performs better than the matrix-based version, while the matrix version with hashing provides the fastest solution when hashing multiple characters together.

- SneakySnakeMat: Slowest due to matrix precomputation and full character comparisons.
- Standard SneakySnake: Faster than SneakySnakeMat but still has room for optimization.
- SneakySnakeMat with Hashing: The fastest implementation, with varying performance based on the number of characters hashed together (from 1 to 100).

### Edit Distance Comparison

The correctness of the implementations was verified by comparing the calculated edit distances to the expected values. The average edit distance decreases as more characters are hashed together, though this does not impact the accuracy of the result in the context of pre-alignment filtering. The trade-off is a faster computation with minimal loss in precision.