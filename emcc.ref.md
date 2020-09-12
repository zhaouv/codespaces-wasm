
一些参考
```shell
docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc test2.cpp -s WASM=1 -o test2.html

docker run \
  --rm -i \
  -v $(pwd):$(pwd) \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  /bin/bash

emcc test1.cpp -o test1.js
emcc test2.cpp -s WASM=1 -o test2.html



docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc test6.cpp test6lib.cc -O3 -s WASM=1 -o test6.html -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap']"

docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc test7.cpp -O3 -o test7.js -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','ccall']" -s "EXPORT_NAME='TEST7'"


docker run \
  --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc test8.cpp -O3 -o test8.js -s NO_EXIT_RUNTIME=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap','ccall']" -s "EXPORT_NAME='TEST8'"
```

```html
<!doctype html>
<html lang=en-us>

<head>
    <meta charset=utf-8>
    <meta content="text/html; charset=utf-8" http-equiv=Content-Type>
    <title>Emscripten-Generated Code</title>

</head>

<body>
    <script>
        /** @class */
        const CArray = function (length, type, Module) {
            this.Module = Module;
            this.type = this.HEAPMAP[type];
            this.HEAP = Module[this.type];
            this.length = length;
            this.BYTES_PER_ELEMENT = this.HEAP.BYTES_PER_ELEMENT;
            this.ptr = Module._malloc(length * this.BYTES_PER_ELEMENT);
            this.offset = this.ptr / this.BYTES_PER_ELEMENT;
            this.data = this.HEAP.subarray(this.offset, this.offset + this.length);
        }
        CArray.from = function(arr, type, Module){
            return new this(arr.length, type, Module).set(arr);
        }
        CArray.prototype.set = function (params) {
            this.data.set(...arguments);
            return this;
        }
        CArray.prototype.free = function (params) {
            this.Module._free(this.ptr);
        }
        CArray.prototype.HEAPMAP = {
            i32: 'HEAP32',
            f32: 'HEAPF32',
            f64: 'HEAPF64',

            int8_t: 'HEAP8',
            uint8_t: 'HEAPU8',
            int16_t: 'HEAP16',
            uint16_t: 'HEAPU16',
            int32_t: 'HEAP32',
            uint32_t: 'HEAPU32',
            float: 'HEAPF32',
            double: 'HEAPF64',

            HEAP8: 'HEAP8',
            HEAPU8: 'HEAPU8',
            HEAP16: 'HEAP16',
            HEAPU16: 'HEAPU16',
            HEAP32: 'HEAP32',
            HEAPU32: 'HEAPU32',
            HEAPF32: 'HEAPF32',
            HEAPF64: 'HEAPF64',
        };

    </script>
    <script>
        const TEST7 = {};
    </script>
    <script src=test7.js></script>
    <script>
        TEST7.onRuntimeInitialized = async _ => {
            var lib = {
                int_add: TEST7.cwrap('int_add', 'i32', ['i32', 'i32']),
                double_add: TEST7.cwrap('double_add', 'f64', ['f64', 'f64']),
                ret_string: TEST7.cwrap('ret_string', 'string', []),
                cat_string: TEST7.cwrap('cat_string', 'string', ['string']),
                int_arr: TEST7.cwrap('int_arr', null, ['i32', 'i32']),
                double_arr: TEST7.cwrap('double_arr', null, ['f64', 'i32']),
            };
            TEST7.lib = lib;
            t1 = new Date();
            console.log(lib.int_add(1.3, 2.3));
            console.log(lib.double_add(1.3, 2.3));
            console.log(lib.ret_string());
            console.log(lib.cat_string('world'));
            { // version 1
                let n = 5;
                let size_type = new Int32Array().BYTES_PER_ELEMENT;
                let arr = new Int32Array(Array.from({ length: n }).map((v, i) => 10 ** (i + 1)))
                let buffer = TEST7._malloc(n * size_type);
                TEST7.HEAP32.set(arr, buffer / size_type);
                lib.int_arr(buffer, n);
                let arr2 = new Int32Array(n);
                arr2.set(TEST7.HEAP32.subarray(buffer / size_type, buffer / size_type + n));
                TEST7._free(buffer);
                console.log(arr2);
            }
            { // version 2
                let n = 5;
                let arr=CArray.from(Array.from({ length: n }).map((v, i) => 10 ** (i + 1)),'i32',TEST7);
                lib.int_arr(arr.ptr, n);
                console.log(arr.data);
                arr.free();
            }
            { // version 1
                let n = 6;
                let size_type = new Float64Array().BYTES_PER_ELEMENT;
                let arr = new Float64Array(Array.from({ length: n }).map((v, i) => 10 ** (i + 1)))
                let buffer = TEST7._malloc(n * size_type);
                TEST7.HEAPF64.set(arr, buffer / size_type);
                lib.double_arr(buffer, n);
                let arr2 = new Float64Array(n);
                arr2.set(TEST7.HEAPF64.subarray(buffer / size_type, buffer / size_type + n));
                TEST7._free(buffer);
                console.log(arr2);
            }
            { // version 2
                let n = 6;
                let arr=CArray.from(Array.from({ length: n }).map((v, i) => 10 ** (i + 1)),'f64',TEST7);
                lib.double_arr(arr.ptr, n);
                console.log(arr.data);
                arr.free();
            }
            t2 = new Date(); console.log(t2 - t1);
        }
    </script>
    <script>
        // ref https://becominghuman.ai/passing-and-returning-webassembly-array-parameters-a0f572c65d97
        const ccallArrays = (func, returnType, paramTypes = [], params, { heapIn = "HEAPF32", heapOut = "HEAPF32", returnArraySize = 1 } = {}) => {

            const heapMap = {}
            heapMap.HEAP8 = Int8Array // int8_t
            heapMap.HEAPU8 = Uint8Array // uint8_t
            heapMap.HEAP16 = Int16Array // int16_t
            heapMap.HEAPU16 = Uint16Array // uint16_t
            heapMap.HEAP32 = Int32Array // int32_t
            heapMap.HEAPU32 = Uint32Array // uint32_t
            heapMap.HEAPF32 = Float32Array // float
            heapMap.HEAPF64 = Float64Array // double

            let res
            let error
            const returnTypeParam = returnType == "array" ? "number" : returnType
            const parameters = []
            const parameterTypes = []
            const bufs = []

            try {
                if (params) {
                    for (let p = 0; p < params.length; p++) {

                        if (paramTypes[p] == "array" || Array.isArray(params[p])) {

                            const typedArray = new heapMap[heapIn](params[p].length)

                            for (let i = 0; i < params[p].length; i++) {
                                typedArray[i] = params[p][i]
                            }

                            const buf = Module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT)

                            switch (heapIn) {
                                case "HEAP8": case "HEAPU8":
                                    Module[heapIn].set(typedArray, buf)
                                    break
                                case "HEAP16": case "HEAPU16":
                                    Module[heapIn].set(typedArray, buf >> 1)
                                    break
                                case "HEAP32": case "HEAPU32": case "HEAPF32":
                                    Module[heapIn].set(typedArray, buf >> 2)
                                    break
                                case "HEAPF64":
                                    Module[heapIn].set(typedArray, buf >> 3)
                                    break
                            }

                            bufs.push(buf)
                            parameters.push(buf)
                            parameters.push(params[p].length)
                            parameterTypes.push("number")
                            parameterTypes.push("number")

                        } else {
                            parameters.push(params[p])
                            parameterTypes.push(paramTypes[p] == undefined ? "number" : paramTypes[p])
                        }
                    }
                }

                res = Module.ccall(func, returnTypeParam, parameterTypes, parameters)
            } catch (e) {
                error = e
            } finally {
                for (let b = 0; b < bufs.length; b++) {
                    Module._free(bufs[b])
                }
            }

            if (error) throw error

            if (returnType == "array") {
                const returnData = []

                for (let v = 0; v < returnArraySize; v++) {
                    returnData.push(Module[heapOut][res / heapMap[heapOut].BYTES_PER_ELEMENT + v])
                }

                return returnData
            } else {
                return res
            }
        }
        // Wrap around cwrap also, as a bonus
        const cwrapArrays = (func, returnType, paramTypes, { heapIn = "HEAPF32", heapOut = "HEAPF32", returnArraySize = 1 } = {}) => {
            return params => ccallArrays(func, returnType, paramTypes, params, { heapIn, heapOut, returnArraySize })
        }
    </script>
</body>

</html>
```