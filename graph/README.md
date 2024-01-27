### Generate graph

#### Installation
- install poetry 
##### Unix 
```sh
curl -sSL https://install.python-poetry.org | python3 -
```

##### Windows
```pwsh
(Invoke-WebRequest -Uri https://install.python-poetry.org -UseBasicParsing).Content | py -
```

Program was last ran using python 3.11.6

run generate graph script
```
poetry install --no-root
poetry run python src/generate.py dev 1000 1000
```

### Development
```
poetry run python -m pip install matplotlib-stubs pandas-stubs
```