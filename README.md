# codespaces-wasm
test codespaces : emcc, wasm

测试codespaces  
不在本地打开这个项目的情况下尝试完成所有以下步骤  
+ 建立并编辑项目(能编辑这个文件就已经是成功了)
+ 配置环境: docker的镜像 emscripten/emsdk
+ build并运行
+ 调试c++ ? 可能要转化成debug c++和debug 网页js两部分

# 配置

安插件就正常安装  
默认是白色, 切换成 [darks+(default dark)] 没作用, 直接改settings.json也没用

# codespaces

配置环境部分  
https://docs.github.com/en/github/developing-online-with-codespaces/configuring-codespaces-for-your-project  
https://github.com/microsoft/vscode-dev-containers/tree/master/containers/codespaces-linux/.devcontainer  
https://github.com/microsoft/vscode-dev-containers/tree/master/containers/codespaces-linux/.devcontainer/library-scripts  
https://github.com/microsoft/vscode-dev-containers/tree/master/containers  

# 默认环境

有 docker gcc node 
没有 julia emcc cmake

# log

启动还能失败的...

代理全开才正常连上, 无法排除

docker -v 过去居然看不到文件  
只能看到目录结构, 看不到任何文件
