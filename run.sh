layout_file="consensus_input/$1_layout.fasta"
alignments_file="consensus_input/$1_alignments_cigar.sam"
result_file="consensus_input/$1_results.fasta"
reads_file="consensus_input/$1_reads.fastq"
reference_file="consensus_input/$1_reference.fasta"

g++ -std=c++11 Sparc.cpp Node.cpp Sequence.cpp KmerGraph.cpp Edge.cpp backbone.cpp Insert.cpp TopologicalSortSearch.cpp -o main

dnadiff $reference_file $layout_file &> /dev/null
res=$(cat out.report | head -19 | tail -1 | grep -Eo '[0-9\.]+$')
echo "Initial accuracy: $res"

for (( i=1; i<=$2; i++))
	do
        echo "\nIteration $i"
        echo "Aligning reads to the layout."
        graphmap/bin/mac/graphmap align -r $layout_file -d $reads_file -o $alignments_file --extcigar &> /dev/null
        echo "Reads aligned."
		./main $layout_file $alignments_file $result_file
        layout_file=$result_file
	done

dnadiff $reference_file $result_file &> /dev/null
res=$(cat out.report | head -19 | tail -1 | grep -Eo '[0-9\.]+$')
echo "Accuracy: $res"



