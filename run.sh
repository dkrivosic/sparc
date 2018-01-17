layout_file="consensus_input/$1_layout.fasta"
alignmnets_file="consensus_input/$1_alignments_cigar.sam"
result_file="consensus_input/$1_results.fasta"
reads_file="consensus_input/$1_reads.fastq"
reference_file="consensus_input/$1_reference.fasta"

g++ -std=c++11 Sparc.cpp Node.cpp Sequence.cpp KmerGraph.cpp Edge.cpp backbone.cpp Insert.cpp TopologicalSortSearch.cpp -o main

for (( i=1; i<=$2; i++))
	do
        echo "Iteration $i"
        echo "Aligning reads to the layout."
        /Users/domagoj/Downloads/graphmap/bin/mac/graphmap align -r $layout_file -d $reads_file -o $alignmnets_file --extcigar &> /dev/null
        echo "Reads aligned."
		./main $layout_file $alignmnets_file $alignmnets_file $result_file
        layout_file=$result_file
	done

dnadiff $reference_file $result_file &> /dev/null

res=$(cat out.report | head -19 | tail -1 | grep -Eo '[0-9\.]+$')
echo "Accuracy: $res"



