# EITI API in OpenAPI format:

## Generate static documentation

### Requirements

* Node.js

### Instructions

1) Move to directory `./eiti-local/docs/openapi`

    ```bash
    cd ./eiti-local/docs/openapi
    ```

2) Install widdershins Node.js module globally (<https://github.com/Mermade/widdershins>)

    ```bash
    sudo npm install -g widdershins
    ```

3) Generate [Shins](https://github.com/mermade/shins) compatible markdown from OpenAPI definition

    ```bash
    widdershins -y ./eiti.yaml -o ./eiti.md
    ```

4) Clone [Shins](https://github.com/Mermade/shins) repository

    ```bash
    git clone https://github.com/Mermade/shins.git ./shins
    ```

5) Generate static documentation

    ```bash
    mv eiti.md shins/source/index.html.md
    cd ./shins && npm install && cd ../
    cd ./shins && node ./shins.js && cd ../
    mkdir ./api/
    cp ./shins/index.html ./api/index.html
    cp ./shins/pub/ ./api/ -r
    cp ./shins/source/ ./api/ -r
    cp ./logo.png ./api/source/images/
    rm -rf ./shins
    ```

6) Open `./eiti-local/docs/openapi/api/index.html` in your preferred browser
