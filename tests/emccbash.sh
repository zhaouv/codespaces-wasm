# bash emccbash.sh \
# emcc test7.cpp -O3 -o test7.js -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','ccall']" -s "EXPORT_NAME='TEST7'"
# ref https://gitlab.com/gitlab-org/gitlab-runner/-/issues/1389
# docker run --volumes-from $(docker ps -aq -f label="com.gitlab.gitlab-runner.cache.dir") --rm -t mycontainer /bin/bash -c "ls $CI_PROJECT_DIR"

# assume that only one container running
# or you should change the content of `--volumes-from`
docker run \
  --rm -it \
  --volumes-from $(docker ps -aq) \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  bash -c "cd $(pwd)&& $*"