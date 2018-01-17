# sparc
The algorithm developed for Bioinformatics class based on:
[Sparc: a sparsity-based consensus algorithm for long erroneous sequencing reads](https://peerj.com/preprints/1401)

## Running

### 1. Get the code
```
Clone this repository
cd sparc
```

### 2. Download the data and install graphmap
```
chmod +x ./prepare_data.sh
./prepare_data.sh
```

### 3. Run the algorithm
#### 3.a lambda
```
chmod +x ./run.sh
./run.sh lambda 1
```

#### 3.b ecoli
```
chmod +x ./run.sh
./run.sh ecoli 1
```

The second argument for run.sh script is number of iterations.