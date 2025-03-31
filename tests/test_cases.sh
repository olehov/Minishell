#!/bin/bash

MINISHELL=./minishell
BASH=/bin/bash
TEST_DIR=tests/tmp
mkdir -p $TEST_DIR

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

total=0
passed=0

run_test() {
    local desc="$1"
    local cmd="$2"

    ((total++))

    echo "$cmd" | $MINISHELL > $TEST_DIR/minishell_raw 2>&1
    echo "$cmd" | $BASH > $TEST_DIR/bash_raw 2>&1

    # Фільтруємо команду та порожні рядки
    grep -vFx "$cmd" $TEST_DIR/minishell_raw | grep -vFx "" > $TEST_DIR/minishell_out
    grep -vFx "$cmd" $TEST_DIR/bash_raw | grep -vFx "" > $TEST_DIR/bash_out

    if diff $TEST_DIR/minishell_out $TEST_DIR/bash_out > /dev/null; then
        echo -e "${GREEN}[OK]${NC} $desc"
        ((passed++))
    else
        echo -e "${RED}[FAIL]${NC} $desc"
        echo "Command: $cmd"
        echo "Expected:"
        cat $TEST_DIR/bash_out
        echo "Got:"
        cat $TEST_DIR/minishell_out
        echo "--------"
    fi
}

# ==================
# TEST CASES BEGIN
# ==================

# Setup
echo "hello from file" > $TEST_DIR/input.txt

# Built-ins
run_test "echo simple" "echo hello"
run_test "echo -n" "echo -n hello"
run_test "pwd" "pwd"
run_test "export TESTVAR" "export TESTVAR=42"
run_test "check TESTVAR" "env | grep TESTVAR"
run_test "set and unset TMPVAR" "export TMPVAR=123"
run_test "check TMPVAR before unset" "env | grep TMPVAR"
run_test "unset TMPVAR" "unset TMPVAR"
run_test "check TMPVAR after unset" "env | grep TMPVAR"
run_test "exit code" "exit 42"

# Pipes
run_test "echo | cat" "echo hello | cat"
run_test "ls | grep .c" "ls | grep .c"

# Redirections
run_test "> output" "echo redirected > $TEST_DIR/out.txt"
run_test "> output check" "cat $TEST_DIR/out.txt"
run_test ">> append" "echo line1 > $TEST_DIR/out.txt"
run_test ">> append second" "echo line2 >> $TEST_DIR/out.txt"
run_test ">> append check" "cat $TEST_DIR/out.txt"
run_test "< input" "cat < $TEST_DIR/input.txt"
run_test "< invalid" "cat < $TEST_DIR/nonexist.txt"

# Variables
run_test "export A=123" "export A=123"
run_test "echo \$A" "echo \$A"
run_test "unset A" "unset A"
run_test "echo \$A after unset" "echo \$A"
run_test "last exit \$?" "ls /invalid"
run_test "echo \$?" "echo \$?"

# Heredoc test
run_test "heredoc with cat" $'cat << EOF
line1
line2
EOF'
cat <<EOF | $MINISHELL > $TEST_DIR/minishell_raw 2>&1
cat << EOF
line1
line2
EOF
EOF

cat <<EOF | $BASH > $TEST_DIR/bash_raw 2>&1
cat << EOF
line1
line2
EOF
EOF

# Витягуємо тільки останні 2 рядки (результат heredoc)
tail -n 2 $TEST_DIR/minishell_raw > $TEST_DIR/minishell_out
tail -n 2 $TEST_DIR/bash_raw > $TEST_DIR/bash_out
((total++))
if diff $TEST_DIR/minishell_out $TEST_DIR/bash_out > /dev/null; then
    echo -e "${GREEN}[OK]${NC} heredoc"
    ((passed++))
else
    echo -e "${RED}[FAIL]${NC} heredoc"
    echo "Expected:"
    cat $TEST_DIR/bash_out
    echo "Got:"
    cat $TEST_DIR/minishell_out
fi

# ===== ДОДАТКОВІ ТЕСТИ =====

# Комбінації пайпів і редіректів
run_test "pipe with redir" "cat $TEST_DIR/input.txt | grep hello > $TEST_DIR/out2.txt"
run_test "check pipe+redir output" "cat $TEST_DIR/out2.txt"

# Змінні з лапками
run_test "export with quotes" "export QSTR=\"Hello World\""
run_test "echo quoted var" "echo \$QSTR"
run_test "single quote test" "echo '\$QSTR'"
run_test "double quote test" "echo \"\$QSTR\""

# Command not found
run_test "unknown command" "nonexistent_cmd"

# Підряд кілька heredoc
run_test "multiple heredoc" $'cat << END
Hello
END
cat << FOO
World
FOO'

# Підряд кілька heredoc в одному запуску
cat <<EOF | $MINISHELL > $TEST_DIR/minishell_raw 2>&1
cat << ONE
a
b
ONE
cat << TWO
c
d
TWO
EOF

cat <<EOF | $BASH > $TEST_DIR/bash_raw 2>&1
cat << ONE
a
b
ONE
cat << TWO
c
d
TWO
EOF

tail -n 4 $TEST_DIR/minishell_raw > $TEST_DIR/minishell_out
tail -n 4 $TEST_DIR/bash_raw > $TEST_DIR/bash_out
((total++))
if diff $TEST_DIR/minishell_out $TEST_DIR/bash_out > /dev/null; then
    echo -e "${GREEN}[OK]${NC} multiple heredoc (inline)"
    ((passed++))
else
    echo -e "${RED}[FAIL]${NC} multiple heredoc (inline)"
    echo "Expected:"
    cat $TEST_DIR/bash_out
    echo "Got:"
    cat $TEST_DIR/minishell_out
fi

# export з пробілами
run_test "export with spaces" "export COMB=\"abc def ghi\""
run_test "echo combined" "echo \$COMB"

# cd та перевірка PWD
run_test "cd into tmp" "cd $TEST_DIR || pwd"

# bad syntax
run_test "invalid pipe" "| ls"
run_test "invalid redir" "echo hi >"

# chaining commands
run_test "chaining with &&" "false && echo fail"
run_test "chaining with ||" "false || echo recover"


# Result

echo ""
echo -e "✅ Passed: ${GREEN}$passed${NC}/$total"
echo ""

rm -rf $TEST_DIR
