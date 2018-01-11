# sparc
The algorithm developed for Bioinformatics class based on:
[Sparc: a sparsity-based consensus algorithm for long erroneous sequencing reads](https://peerj.com/preprints/1401)

For **CodeRunner** extension, add the next line in `.vscode/setting.json`:

`"code-runner.executorMap": {
        "cpp": "g++ -std=c++11 sparc/sparc.cpp sparc/Sequence.cpp -o main && ./main"
    }`

## Running

### 1. Clone [GraphMap](https://github.com/isovic/graphmap.git) and run:

`./bin/Linux-x64/graphmap -r sparc/consenus_input/lambda_layout.fasta -d sparc/consenus_input/lambda_reads.fastq -o sparc/consenus_input/lambda_alignments_cigar.sam --extcigar`

This will create .sam file with alignments (aligning layout and sequences)

### 2. Run `sparc.cpp`

Run it from folder **sparc** with terminal command:

`g++ -std=c++11 sparc/sparc.cpp sparc/Sequence.cpp -o main && ./main` 

Or with CodeRunner extension for VSCode.