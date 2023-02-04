# SEL0429 - Bioengenharia-Ocular II
Projeto da disciplina SEL0429 - Bioengenharia Ocular II (2022), cujo objetivo é desenvolver um sistema para medir a qualidade de armações de óculos de sol usando um simulador de intensidade de albedo.


# Introdução
A radiação UV pode causar uma série de dados no olho humano, inclusive acredita-se que ela é uma das causadoras da catarata. Os óculos de sol são a principal forma de proteção contra essa forma de radiação no dia a dia. Para regulamentar e padronizar os modelos de óculos de sol existe a norma [ISO12312-1:2021], as quais estabelecem o padrão para a proteção ocular, bem como os limites para transmissão da radiação ultravioleta, particularmente UVA e UVB em função das categorias dos óculos. No entanto, elas abrangem exclusivamente as lentes, ignorando totalmente a armação dos óculos que possuem um papel fundamental nessa proteção.

## Albedo
O principal fenômeno físico analisado no projeto para medir a qualidade de proteção dos óculos é o Albedo, que pode ser definido como a medida da reflectância, quantidade de radiação solar refletida, por  uma superfície. Ele é calculado como a razão entre a quantidade de radiação refletida e a quantidade de radiação recebida. Em termos geográficos, o albedo representa a relação entre a quantidade de luz refletida pela superfície terrestre e a quantidade de luz recebida do Sol, o albedo  da maior parte das áreas terrestres está na faixa de 0,1 a 0,4, em uma escala de 0 a 1.

# Lógica de programação
O programa é feito a fim de executar todo o desejado no projeto. Esse seguirá juntamente com o display, sendo executado determinadas partes dependendo da tela que está presente. Primeiramente, após se determinar qual óculos será trabalhado, liga-se todos os LEDs no máximo e mede o valor do sensor, e desliga-se os LEDs. Então, escolhido-se o cenário que será trabalhado, liga-se os LEDs conforme o escolhido, e captura-se o valor do sensor, e desliga-se os LEDs.

Após isso, o usuário abre a esfera, colaca os óculos e fecha a esfera noavamente. Então liga-se os LEDs no máximo e mede-se o valor do sensor, dessa vez com os óculos; e depois liga-se os LEDs conforme o cenário escolhido e mede-se o valor do sensor com os óculos. Após isso realiza-se os cálculos de proteção desse óculos, e mostra os resultados na tela do display. Então salva-se no cartão SD os dados do óculos utilizado, e a sua porcentagem de proteção para a iluminação total.

- Para realizar o controle das fitas de LED foi utilizada a biblioteca [`Adafruit_PWMServoDriver.h`]()
