#!/usr/bin/env python

import polars as pl
import argparse
from pathlib import Path
from numpy import random
import duckdb


def create_test_dataset(n: int, output_path: Path):
    chunk_size = 100_000
    chunks = n // chunk_size
    with open(output_path, "w") as f:
        for chunk in range(chunks):
            df = pl.DataFrame(
                {
                    "timestamp": random.randint(
                        1000000000000, 1700514457281, chunk_size
                    ),
                    "client_id": random.randint(0, 15000, chunk_size),
                    "type": random.choice(
                        ["Lorem", "Ipsum", "Dolor", "Amet"], chunk_size
                    ),
                    "reading": random.random(chunk_size) * 1000,
                }
            )

            # Append mode for CSV writing
            mode = "a" if chunk > 0 else "w"
            header = False if chunk > 0 else True
            df.write_csv(f, has_header=header)
            print(f"Chunk {chunk + 1}/{chunks} written")

    print(f"Dataset created at {output_path}")


def convert_to_parquet(csv_path: Path, parquet_path: Path, chunk_size: int = 1_000_000):
    csv_iter = pl.scan_csv(csv_path)
    parquet_writer = None

    for df_chunk in csv_iter:
        if parquet_writer is None:
            parquet_writer = pl.ParquetWriter(parquet_path, df_chunk.schema)

        parquet_writer.write(df_chunk)
        print("Chunk written")

    if parquet_writer is not None:
        parquet_writer.close()

    print(f"Dataset converted to Parquet at {parquet_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--num_rows", type=int, default=100_000_000)
    parser.add_argument("-o", "--output_path", type=Path, default="data/dataset.csv")
    parser.add_argument(
        "-p", "--parquet_path", type=Path, default="data/dataset.parquet"
    )
    args = parser.parse_args()

    # create_test_dataset(n=args.num_rows, output_path=args.output_path)
    convert_to_parquet(csv_path=args.output_path, parquet_path=args.parquet_path)
