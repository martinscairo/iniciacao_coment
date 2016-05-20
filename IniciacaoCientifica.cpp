//========================================================================================
// Name        : IniciacaoCientifica.cpp
// Author      : Joao Flavio Vieira de Vasconcellos
// Version     : 1.0
// Description : programa para praticar normas etc etc 
//
// Copyright   : Copyright (C) <2016>  João Flávio Vasconcellos (jflavio at iprj.uerj.br)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//========================================================================================


//============================================================================
// C++ Includes
//============================================================================
#include <iostream>
#include <string>
#include <vector>


//============================================================================
// outros Includes
//============================================================================
#include <libconfig.h++>


//============================================================================
// suas bibliotecas Includes
//============================================================================
#include <MyData.h>

//============================================================================
// typedefs
//============================================================================
std::vector<int>                            VecInt;


//============================================================================
// Cabeçalhos - protótipos
//============================================================================
int LeituraArquivoIni (MyData&);
int LeituraArquivoDados (MyData&);

//============================================================================
// main function
//============================================================================
#undef __FUNCT__
#define __FUNCT__ "int main(int, char**)"
int main(int argc, char** argv) {

//============================================================================
// Leitura do arquivo de configuracao IniciacaoCientifica.ini
//============================================================================    
MyData              mydata;

    LeituraArquivoIni(mydata);
    
      std::cout << "\nArquivo de entrada de dados: " 
              << mydata.arquivo_entrada
              << "\n";
    
    std::cout << "\nArquivo de saida de dados: " 
              <<  mydata.arquivo_saida
              << "\n";   
    LeituraArquivoDados (mydata);
    return 0;
}

#undef __FUNCT__
#define __FUNCT__ "int LeituraArquivoIni (MyData&)"

int LeituraArquivoIni (MyData& _mydata)
{
const std::string           FILENAME("IniciacaoCientifica.ini"); //arquivo do tipo ini que contém strings
libconfig::Config           cfg_ini;                             //variável libconfig para ler arquivo de dados
int                         erro_line;                           // variável auxiliar

     try          //sintaxe para manipulação de erros
    {
        erro_line = __LINE__ + 1;                //variável line previamente definida
        cfg_ini.readFile(FILENAME.c_str());      //variável para ler o arquivo de dados
    }
     
     // CATCH especifica o que fazer a partir dos erros
    catch(const libconfig::FileIOException& _fioex) //confere existência do arquivo
    {
        
        std::cout << "Erro encontrado em:                     " 
                  << __FILE__
                  << "\nNa funcao: "                        
                  << __FUNCT__
                  << "\nNa linha: "
                  << erro_line
                  << "\nArquivo '"
                  << FILENAME
                  << " nao foi encontrado."
                  << "\nExecucao cancelada.\n\n\n";
   
                         
        exit(EXIT_FAILURE);
    }
    catch(const libconfig::ParseException& _pex)     //ENCONTRA PROBLEMAS DE LEITURA
    {
        std::cout << "Erro encontrado em:                         "
                  << __FILE__
                  << "\nNa funcao: "                        
                  << __FUNCT__
                  << "\nNa linha: "
                  << erro_line
                  << "\nProblema encontrado na leitura da linha"
                  << _pex.getLine()
                  << " do arquivo "
                  << _pex.getFile()
                  << "\nExecucao cancelada.\n\n\n";
        
        exit(EXIT_FAILURE);
    }

const libconfig::Setting& dados_ini = cfg_ini.getRoot(); //apenas definição de variáveis
//arquivo de entrada, arquivo de saída e arquivo de valor

//std::string                           arq_saida; 

//criação de vetor string com as variáveis que interessam ao programa
std::vector<std::string>              vecini   {"arquivo_dados",
                                                "arquivo_saida",
                                                "valor_entrada"
                                      };


float                                   dt1;

//palavras-chave na memória
// procura igualdades no arquivo de dados

//    dados_ini.lookupValue("arquivo_dados", _mydata.arquivo_entrada);  //associa variável ao nome
//    dados_ini.lookupValue("arquivo_saida", _mydata.arquivo_saida);  
//    dados_ini.lookupValue("valor_entrada", dt1);    
    
//conferindo se as três VARIÁVEIS estão no arquivo
   
    for (auto &ix : vecini) {
        if (!dados_ini.exists(ix)){
            erro_line= __LINE__ -2;
            std::cout<< "Variável não encontrada: " << ix << std :: endl;
            exit (EXIT_FAILURE);
        }
    }


    dados_ini.lookupValue(vecini[0], _mydata.arquivo_entrada);  //associa variável ao nome
    dados_ini.lookupValue(vecini[1], _mydata.arquivo_saida);  
    dados_ini.lookupValue(vecini[2], dt1);    
    
//    std::cout << "\nArquivo de entrada de dados: " 
//              << _mydata.arquivo_entrada
//              << "\n";
//    
//    std::cout << "\nArquivo de saida de dados: " 
//              <<  _mydata.arquivo_saida
//              << "\n";   
//    
//    std::cout << "\nDt1: "
//              << dt1;
              
    
}

#undef __FUNCT__        //zera a definição
#define __FUNCT__ "int LeituraArquivoDados (MyData&)" 

//diretivas de compilação -> só existem e só funcionam na compilação, 
//não existem na execução -> variável funct com o nome da função a ser rodada

// exemplo #define degub -> útil para selecionar as partes do programa a serem compiladas 
// (pode ser comentado ou não)
// ...
// ifdef debug ->>> só compila se debug estiver definido
//...
//endif

//include é uma diretiva de compilação -> assimila o arquivo e compila no código

int LeituraArquivoDados (MyData& _mydata)
{
//    std::cout << "Vou ler o arquivo: " << _mydata.arquivo_entrada << std::endl;
    
    libconfig::Config           cfg_dados; //variável libconfig para ler arquivo de dados
    int erro_line;
    
     try //confere se há erros no arquivo de leitura
    {
//        erro_line = __LINE__ + 1;
        cfg_dados.readFile(_mydata.arquivo_entrada.c_str());
    }
    catch(const libconfig::FileIOException& _fioex) //caso o arquivo nao exista
    {
        
        std::cout << "Erro encontrado em:                         "
                  << __FILE__
                  << "\nNa funcao: "                        
                  << __FUNCT__
                  << "\nNa linha: "
                  << erro_line
                  << "\nArquivo '"
                  << _mydata.arquivo_entrada
                  << "' nao foi encontrado."
                  << "\nExecucao cancelada.\n\n\n";
   
                         
        exit(EXIT_FAILURE);
    }
    catch(const libconfig::ParseException& _pex) //caso haja erro de leitura
    {
//        std::cout << "Erro encontrado em:                         "
//                  << __FILE__
//                  << "\nNa funcao: "                        
//                  << __FUNCT__
//                  << "\nNa linha: "
//                  << erro_line
//                  << "\nProblema encontrado na leitura da linha"
//                  << _pex.getLine()
//                  << " do arquivo "
//                  << _pex.getFile()
//                  << "\nExecucao cancelada.\n\n\n";
        
        exit(EXIT_FAILURE);
    }
}












