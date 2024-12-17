#!/bin/awk -f

BEGIN { output_file = ""; }
/^Process: / {
    if (output_file != "") {
        close(output_file);
    }
    split($0, arr, /[\(\)]/);
    process_name = substr(arr[1], 9);
    pid = substr(arr[2], 6);
    gsub(/ /, "", process_name);
    output_file = process_name "_" pid ".txt";
}
{
    if (output_file != "") {
        print $0 > output_file;
    }
}
END {
    if (output_file != "") {
        close(output_file);
    }
}