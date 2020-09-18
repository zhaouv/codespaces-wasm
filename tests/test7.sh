cd "$(dirname "$0")"
bash emccbash.sh \
emcc test7.cpp -O3 -o test7.js -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','ccall']" -s "EXPORT_NAME='TEST7'"
