#include <stdio.h>

int main() {
    // Tabuleiro principal (0 = água, 3 = navio, 1 = habilidade)
    int tabuleiro[10][10] = {0};
    
    // Matrizes de habilidades (0 = não afetado, 1 = afetado)
    int cone[5][5] = {0};
    int cruz[5][5] = {0};
    int octaedro[5][5] = {0};
    
    // Navios (todos representados por 3)
    int navio_horizontal[3] = {3, 3, 3};
    int navio_vertical[3] = {3, 3, 3};
    int navio_diagonal1[3] = {3, 3, 3};
    int navio_diagonal2[3] = {3, 3, 3};
    
    // Posições das habilidades
    int linha_habilidade = 3;
    int coluna_habilidade = 5;
    
    // Variáveis de controle
    int i, j, linha, coluna, largura, inicio;
    int tentativa, pode_colocar, colocou_horizontal = 0;
    int colocou_vertical = 0, colocou_diagonal1 = 0, colocou_diagonal2 = 0;

    // Colocação do navio horizontal
    for(tentativa = 0; tentativa < 100 && !colocou_horizontal; tentativa++) {
        linha = tentativa % 10;
        coluna = (tentativa / 10) % 8;
        
        pode_colocar = 1;
        for(i = 0; i < 3; i++) {
            if(linha >= 10 || coluna+i >= 10 || tabuleiro[linha][coluna+i] != 0) {
                pode_colocar = 0;
                break;
            }
        }
        
        if(pode_colocar) {
            for(i = 0; i < 3; i++) {
                tabuleiro[linha][coluna+i] = navio_horizontal[i];
            }
            colocou_horizontal = 1;
        }
    }

    // Colocação do navio vertical
    for(tentativa = 0; tentativa < 100 && !colocou_vertical; tentativa++) {
        linha = tentativa % 8;
        coluna = (tentativa / 8) % 10;
        
        pode_colocar = 1;
        for(i = 0; i < 3; i++) {
            if(linha+i >= 10 || coluna >= 10 || tabuleiro[linha+i][coluna] != 0) {
                pode_colocar = 0;
                break;
            }
        }
        
        if(pode_colocar) {
            for(i = 0; i < 3; i++) {
                tabuleiro[linha+i][coluna] = navio_vertical[i];
            }
            colocou_vertical = 1;
        }
    }
    
        // COLOCAÇÃO DO NAVIO DIAGONAL PRINCIPAL (i,i)
        for(int tentativa = 0; tentativa < 100 && !colocou_diagonal1; tentativa++) {
            linha = tentativa % 8;  // Garante espaço para 3 casas na diagonal
            coluna = linha;         // Diagonal principal (linha = coluna)
            
            pode_colocar = 1;
            // Verifica se as 3 posições diagonais estão livres
            for(i = 0; i < 3; i++) {
                if(linha+i >= 10 || coluna+i >= 10 || tabuleiro[linha+i][coluna+i] != 0) {
                    pode_colocar = 0;
                    break;
                }
            }
            
            // Se todas posições estiverem livres, coloca o navio
            if(pode_colocar) {
                for(i = 0; i < 3; i++) {
                    tabuleiro[linha+i][coluna+i] = 3; // Marca como navio
                }
                colocou_diagonal1 = 1;
            }
        }
    
        // COLOCAÇÃO DO NAVIO DIAGONAL SECUNDÁRIA (i,9-i)
        for(int tentativa = 0; tentativa < 100 && !colocou_diagonal2; tentativa++) {
            linha = tentativa % 8;  // Garante espaço para 3 casas
            coluna = 7 - (tentativa % 8); // Diagonal secundária (coluna diminui)
            
            pode_colocar = 1;
            // Verifica se as 3 posições diagonais estão livres
            for(i = 0; i < 3; i++) {
                if(linha+i >= 10 || coluna-i < 0 || tabuleiro[linha+i][coluna-i] != 0) {
                    pode_colocar = 0;
                    break;
                }
            }
            
            // Se todas posições estiverem livres, coloca o navio
            if(pode_colocar) {
                for(i = 0; i < 3; i++) {
                    tabuleiro[linha+i][coluna-i] = 3; // Marca como navio
                }
                colocou_diagonal2 = 1;
            }
        }

    // Criar padrão de cone
    for(i = 0; i < 5; i++) {
        largura = i + 1;
        inicio = (5 - largura) / 2;
        for(j = inicio; j < inicio + largura; j++) {
            cone[i][j] = 1;
        }
    }
    
    // Criar padrão de cruz
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(i == 2 || j == 2) {
                cruz[i][j] = 1;
            }
        }
    }
    
    // Criar padrão de octaedro
    for(i = 0; i < 5; i++) {
        if(i < 3) {
            largura = 2*i + 1;
        } else {
            largura = 2*(4-i) + 1;
        }
        inicio = (5 - largura) / 2;
        for(j = inicio; j < inicio + largura; j++) {
            octaedro[i][j] = 1;
        }
    }
    
    // Aplicar cone no tabuleiro (valor 1)
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(cone[i][j] == 1) {
                linha = linha_habilidade + i - 2;
                coluna = coluna_habilidade + j - 2;
                if(linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10) {
                    if(tabuleiro[linha][coluna] == 0) { // Só marca se for água
                        tabuleiro[linha][coluna] = 1;
                    }
                }
            }
        }
    }
    
    // Aplicar cruz no tabuleiro (valor 1)
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(cruz[i][j] == 1) {
                linha = linha_habilidade + i - 2 + 3;
                coluna = coluna_habilidade + j - 2;
                if(linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10) {
                    if(tabuleiro[linha][coluna] == 0) {
                        tabuleiro[linha][coluna] = 1;
                    }
                }
            }
        }
    }
    
    // Aplicar octaedro no tabuleiro (valor 1)
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(octaedro[i][j] == 1) {
                linha = linha_habilidade + i - 2 + 6;
                coluna = coluna_habilidade + j - 2;
                if(linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10) {
                    if(tabuleiro[linha][coluna] == 0) {
                        tabuleiro[linha][coluna] = 1;
                    }
                }
            }
        }
    }
    
    // Mostrar tabuleiro
    printf("Batalha Naval com Habilidades Especiais:\n");
    printf("   A B C D E F G H I J\n");
    
    for(linha = 0; linha < 10; linha++) {
        printf("%2d ", linha+1);
        for(coluna = 0; coluna < 10; coluna++) {
            if(tabuleiro[linha][coluna] == 0) printf("0 ");
            else if(tabuleiro[linha][coluna] == 3) printf("3 ");
            else printf("1 "); // Habilidades
        }
        printf("\n");
    }

    return 0;
}