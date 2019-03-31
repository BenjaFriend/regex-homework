valgrind --leak-check=full --log-file=errors ./bin/Regex_HW -c test.conf


echo "VALGRIND AT EXIT: "
grep 'at exit' errors
