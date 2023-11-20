#!/bin/bash

set -e # stop on error
#
# DuckDB CLI
# 
wget "https://github.com/duckdb/duckdb/releases/download/v0.9.2/duckdb_cli-linux-aarch64.zip"
unzip duckdb_cli-linux-aarch64.zip
rm duckdb_cli-linux-aarch64.zip

