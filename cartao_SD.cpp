#include "cartao_SD.hpp"

bool salvar_dados(const char *dados)
{

    if (!SD.begin(porta_SD))
    {
        return false;
    }

    bool existencia_arquivo = SD.exists("data3.txt");
    File dataFile = SD.open("data3.txt", FILE_WRITE);
    const char *cabecalho = "olá pessoal!";

    if (!existencia_arquivo)
    {
        dataFile.println(cabecalho);
        dataFile.println(dados);
    }else{
        dataFile.println(dados);
    }


    dataFile.close();

    return true;
}