#include <iostream>
#include <map>
#include <string>
#include "logic/engine.hpp"

int main() {
    std::string htmlBalanceado = R"(
        <!DOCTYPE html>
        <html>
        <head>
          <title>Mi pagina web</title>
        </head>
        <body>

          <h1>Mi pagina web</h1>
          <h2>Subtitulo 1</h2>
          <p>Parrafo 1</p>
          <p>Parrafo 2</p>
          <p>Parrafo 3</p>
          <p>Parrafo 4</p>
          <p>Parrafo 5</p>
          <h2>Subtitulo 2</h2>
          <p>Parrafo 6</p>
          <p>Parrafo 7</p>
          <p>Parrafo 8</p>
          <p>Parrafo 9</p>
          <p>Parrafo 10</p>
          <div class="container">
            <p>hola mundo</p>
            <p>el resultado de 10/2 es 5 10 < 5 </p>
            <a rel="noopener noreferrer" href="https://www.ejemplo.com"/>
            <link real="stylesheet" href="https://www.ejemplo1.com"/> 
            <img src="https://www.ejemplo de imagen.com" />
          </div>
        </body>
        </html>
    )";

    if (esHTMLBalanceado(htmlBalanceado)) {
        std::cout << "El HTML esta bien balanceado." << std::endl;
    } else {
        std::cout << "El HTML esta mal balanceado." << std::endl;
    }

    return 0;
}