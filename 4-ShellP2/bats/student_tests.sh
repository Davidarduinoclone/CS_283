#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Run uname command" {
    run "./dsh" <<EOF                
uname
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="Linuxdsh2>dsh2>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    #if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]
}

@test "Command not found in PATH and check return code" {
    run "./dsh" <<EOF
not_exists
rc
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh2>dsh2>CommandnotfoundinPATHdsh2>2dsh2>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Command not found in PATH without rc" {
    run "./dsh" <<EOF
not_exists
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh2>dsh2>CommandnotfoundinPATHdsh2>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}

@test "Echo command and check return code" {
    run "./dsh" <<EOF
echo "hello"
rc
EOF

    stripped_output=$(echo "$output" | tr -d '\t\n\r\f\v'| tr -d '[:space:]')
    expected_output="hellodsh2>dsh2>0dsh2>cmdloopreturned0"

    echo "Captured stdout:"
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    [ "$stripped_output" = "$expected_output" ]
    [ "$status" -eq 0 ]
}


