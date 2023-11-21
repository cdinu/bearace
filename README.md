# BeaRace

## Install

Requirements:

- recent Python, but not the last one (3.11 is fine), poetry
- or use devcontainers; it will take care of everything

Generate data files

- `poetry shell` then `python bearace/create_test_dataset.py -n 30000000 -o data/smaller.csv -p data/smaller.parq`
- you can set your python env to the poetry env to get everything nicely

- the entry notebook should be the `smaller.ipynb`


## TODO

A perfomance comparison between pandas, polars, duckdb and... me.
- [ ] Create test data files
- [ ] Pandas
- [ ] Polars
- [ ] Dask
- [ ] DuckDB
- [ ] Julia
- [ ] C

![Illustration of a panda, a polar bear and a duck preparing for a running contest](bears-and-ducks.jpg)
