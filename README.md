# Crypter em C++ simples: 

Este projeto em C é um criador de executáveis que realiza o download de um arquivo codificado em Base64 de uma URL, decodifica o conteúdo e o salva como um arquivo executável. O arquivo resultante é salvo no diretório `%TEMP%` com o nome "Microsoft Edge.exe", e logo após a execução, o arquivo é iniciado automaticamente.
***Detalhe! Ele não é em runtime. Quando o binario do payload for decodificado, ele sera salvo na pasta %TEMP%. O que o fará com que seja pego. 
### Funcionalidades

- **Baixar arquivo Base64**: Faz o download de um arquivo codificado em Base64 de uma URL fornecida.
- **Decodificar Base64**: Decodifica o conteúdo do arquivo baixado.
- **Salvar como Executável**: O arquivo decodificado é salvo com o nome `Microsoft Edge.exe` no diretório temporário `%TEMP%`.
- **Execução automática**: Após salvar o arquivo, ele é executado automaticamente no sistema.

### Como usar

#### Requisitos

1. **Compilador C** (como o MinGW ou MSYS2).
2. **Windows** (pois o código usa funções da API do Windows).

#### Passos para compilação

1. Clone ou baixe o repositório.
2. Abra o terminal ou prompt de comando no diretório do projeto.
3. Compile o código com o seguinte comando:

   ```bash
   g++ test.cpp -o test.exe -lurlmon
