#!/bin/bash

# Name: Adam Láníček, Holden Ďurovič, Honza Novotný, Drahník Lukáš
# Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
# Date: 14.11.2018
# Email: <xlanic04@stud.fit.vutbr.cz>, <xdurov01@stud.fit.vutbr.cz>, <xnovot1e@stud.fit.vutbr.cz>, <xdrahn00@stud.fit.vutbr.cz>
# File: tests.sh
# Description: Bash script to run the program with different graphs and parameters to test its functionality

OUTPUT_DIR=./tests/output
INPUT_DIR=./tests/graphs_in
REF_OUTPUT_DIR=./tests/ref_paths_out
PARAMS_DIR=./tests/params_in
DIFF_DIR=./tests/diff

if [ -d "$OUTPUT_DIR" ]; then
    rm -r "$OUTPUT_DIR"
fi

if [ -d "$DIFF_DIR" ]; then
    rm -r "$DIFF_DIR"
fi

mkdir "$OUTPUT_DIR"
#mkdir "$DIFF_DIR"

for graph in "$INPUT_DIR"/*.in; do
    graph_no=$(basename "$graph" .in)
    param_f="$PARAMS_DIR"/"$graph_no".par
    par_no=$(basename "$param_f" .par)
    param_row=0
    while read -r params; do
        ((param_row=param_row+1))
        hpath_output="$graph_no"."$param_row"
        hpath_output_path="$OUTPUT_DIR"/"$hpath_output"".out"
        hpath_ref_output_path="$REF_OUTPUT_DIR"/"$hpath_output"".out"
        $1 $params $graph > "$hpath_output_path" 2> /dev/null
        ret_code=$?
        rc_file="$REF_OUTPUT_DIR"/"$hpath_output"".rc"
        
        if [ -f $rc_file ]; then
            ref_rc=$(head -n 1 $rc_file)
        else
            ref_rc=0
        fi

        if [ -f "$hpath_ref_output_path" ]; then
            match=0
            ref_line_cnt=$(wc -l < "$hpath_ref_output_path")
            while read -r ref_file_line; do # we read in the first line from the reference output file
                out_line_index=0
                while read -r output_line; do
                    out_line_index=$((out_line_index+1))
                    if [[ "$output_line" == "$ref_file_line" ]]; then # we found a line match
                        for edge_index in $(seq 1 "$ref_line_cnt"); do # now we are iterating over the next $ref_line_cnt lines to find out if we have a match
                            ref_file_line_content=$(sed -n "$edge_index"p "$hpath_ref_output_path")
                            out_file_line_ptr=$((out_line_index + edge_index - 1))
                            output_file_line_content=$(sed -n "$out_file_line_ptr"p "$hpath_output_path")
                            if [[ "$ref_file_line_content" != "$output_file_line_content" ]]; then # n-th line does not match, we break from the for loop
                                match=0
                                break
                            fi
                            if [ $edge_index -eq $ref_line_cnt ]; then
                                match=1
                                break
                            fi
                        done
                    fi
                    if [ $match -eq 1 ]; then
                        break
                    fi
                done < "$hpath_output_path"
                if [ $match -eq 1 ]; then
                    break
                fi
            done < "$hpath_ref_output_path"
            # Just uncomment the first line and comment the next one if you do not want the diff data to be displayed in the command line as well
            #diff "$hpath_output_path" "$REF_OUTPUT_DIR"/"$hpath_output"".out" > "$DIFF_DIR"/"$hpath_output"".diff"
            #diff "$hpath_output_path" "$REF_OUTPUT_DIR"/"$hpath_output"".out" | tee "$DIFF_DIR"/"$hpath_output"".diff"
        else
            echo -e "\tERROR: No reference output found for the test $hpath_output! Params: $params"
            continue
        fi
        if [ $match -eq 1 ] && [ $ret_code -eq $ref_rc ]; then
            echo "*** TEST "$hpath_output" ***PASSED***! Launch params: $params"
        elif [ $match -eq 1 ]; then
            echo "TEST "$hpath_output" PASSED with unexpected return codes (exp/real): $ref_rc/$ret_code. Launch params: $params"
        elif [ $match -eq 0 ]; then
            echo "TEST "$hpath_output" FAILED! Launch params: $params"
        #elif [ ${PIPESTATUS[0]} -eq 1 ]; then
         #   echo "*** TEST "$hpath_output" FAILED because of unexpected return code! Params: $params, return codes (exp/real): $ref_rc/$ret_code"
        #elif [ ${PIPESTATUS[0]} -gt 1 ]; then
        #    echo "*** TEST "$hpath_output" DIFF ERROR!"
        fi
    
    done < "$param_f"
done
