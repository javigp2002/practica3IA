# include "AIPlayer.h"
# include "Parchis.h"
#include <limits.h>

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

    static const int IS_EATING_MOVE = 12;
    static const int IS_GOAL_SCORE = 10;

    static const int FINAL_QUEUE = 8;
    static const int HOME_PIECE = 2;
    static const int SAFE_PIECE = 12;
    
    static const int DIST_GOAL_MAX = 80;


bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.


    /*
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

   */
    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    double alpha = menosinf; //comprobar
    double beta = masinf; //comprobar
    int valor;

    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, 0, c_piece, id_piece, dice, alpha, beta, miValoracion);
            
            break;
        case 1:
           valor = Poda_AlfaBeta(*actual, 0, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 2:
           // 
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;


}
void AIPlayer::thinkAleatorio(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }
}

void AIPlayer::thinkAleatorioMasInteligente(color & c_piece, int & id_piece, int & dice) const{
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);

    vector<int> current_dices_que_pueden_mover_ficha;

    for (int i = 0; i < current_dices.size(); i++)
    {
        current_pieces = actual->getAvailablePieces(c_piece, current_dices[i]);
        if (current_pieces.size() > 0)
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
    }
    
    // Elijo un dado de forma aleatoria.
    if (current_dices_que_pueden_mover_ficha.size() == 0){
        dice = current_dices[rand() % current_dices.size()];
        id_piece = SKIP_TURN;
    } else {
         dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];
         current_pieces = actual->getAvailablePieces(c_piece,dice);

         id_piece=current_pieces[rand()%current_pieces.size()];
    }
    id_piece =id_piece;
}
void AIPlayer::thinkFichaMasAdelantada(color & c_piece, int & id_piece, int & dice) const{

    thinkAleatorioMasInteligente(c_piece,id_piece,dice);

    vector<int> current_pieces = actual->getAvailablePieces(c_piece,dice);

    int id_ficha_mas_adelantada=-1;
    int min_distancia_meta = 9999;
    for (size_t i = 0; i < current_pieces.size(); i++)
    {   
        int distancia_meta = actual->distanceToGoal(c_piece,current_pieces[i]);
        if (distancia_meta <min_distancia_meta){
            min_distancia_meta=distancia_meta;
            id_ficha_mas_adelantada=current_pieces[i];
        }
    }
    
    if (id_ficha_mas_adelantada == -1)
        id_piece = SKIP_TURN;
    else
        id_piece=id_ficha_mas_adelantada;
}   

void AIPlayer::thinkMejorOpcion(color & c_piece, int & id_piece, int & dice) const{
    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece,last_dice);

    bool me_quedo_con_esta_accion=false;

    while(!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion){
        if(siguiente_hijo.isEatingMove() || siguiente_hijo.isGoalMove() || 
        (siguiente_hijo.gameOver() && siguiente_hijo.getWinner() == this->jugador)){
            me_quedo_con_esta_accion=true;
        } else {
            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece,last_dice);
        }
    }

    if(me_quedo_con_esta_accion){
        c_piece = last_c_piece;
        id_piece=last_id_piece;
        dice = last_dice;
    } else {
        thinkFichaMasAdelantada(c_piece,id_piece,dice);
    }
}

 double AIPlayer::puntuacionJugador(const Parchis &estado, vector<color> my_colors, vector<color> enemy_colors, int jugador){
    int puntuacion_jugador = 0;
    
    
    // Recorro todaslas fichas de mi jugador
    if (estado.isEatingMove())
        if (estado.getCurrentPlayerId()== jugador){
            puntuacion_jugador += IS_EATING_MOVE;
        }
    if (estado.isGoalMove())
        if (estado.getCurrentPlayerId()== jugador){
            puntuacion_jugador += IS_EATING_MOVE;
        }
    // Recorro colores de mi jugador.
    for (int i = 0; i < my_colors.size(); i++){
        color c = my_colors[i];
        puntuacion_jugador += (num_pieces - estado.piecesAtHome(c))*HOME_PIECE ;
        puntuacion_jugador+= estado.piecesAtGoal(c)*IS_GOAL_SCORE;
        
        // Recorro las fichas de ese color.
        for (int j = 0; j < num_pieces; j++){
            // Valoro positivamente que la ficha esté en casilla segura o meta.
            Box piezaActual = estado.getBoard().getPiece(c, j);
            if (piezaActual.type != box_type::home){ 
                if (estado.isSafePiece(c, j) || estado.isWall(piezaActual) != color::none){
                    puntuacion_jugador+=SAFE_PIECE;

                }
                if (piezaActual.type == box_type::final_queue){
                    puntuacion_jugador += FINAL_QUEUE- estado.distanceToGoal(c,j);
                }
                
                puntuacion_jugador+= DIST_GOAL_MAX - estado.distanceToGoal(c,j);
            
            
            }
        }
    }
    
        
    return puntuacion_jugador;
}

double AIPlayer::miValoracion(const Parchis &estado, int jugador){

    int ganador = estado.getWinner();
    int oponente = (jugador+1)%2;
    if (ganador == jugador){
        return gana;
    }
    else if (ganador == oponente) {
        return pierde;
    }

    vector<color> ally = estado.getPlayerColors(jugador);
    vector<color> enemys = estado.getPlayerColors(oponente);

    return puntuacionJugador(estado,ally,enemys,jugador)- puntuacionJugador(estado,enemys,ally,oponente);

}

/*--------------------------------------------------------------------------------------*/
double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int profundidad, color &c_piece, int &id_piece, 
int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const{
    
    if (profundidad == PROFUNDIDAD_ALFABETA || actual.gameOver()){
        
        return (heuristic(actual, this->id) );
    }
  

    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;

    Parchis siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece,last_dice);
    double evaluacion, maximo, minimo;

    bool podar=false;
    //Poda Alfa
    if (this->id == actual.getCurrentPlayerId()){ //MAX
        maximo = menosinf; //comprobar

        while(!(siguiente_hijo == actual) && !podar){
           
            evaluacion = Poda_AlfaBeta(siguiente_hijo,profundidad+1, last_c_piece,last_id_piece,last_dice,alpha,beta,heuristic);
            
            
            if (maximo < evaluacion){ // pensar si < o <= - primero o ultimo
                maximo = evaluacion;
                if (profundidad == 0){
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                    cout<<endl << endl<< c_piece << "|"<< id_piece << "|"<< dice << "-" << evaluacion<< endl << endl;
                }
            }

            alpha = max(alpha,evaluacion);

            if (beta <= alpha)
                podar = true;
            else
                siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece,last_dice);
        }

       
        //actualizamos el valor del padre 
        return maximo;
    } else {
        minimo = masinf; //comprobar

        while(!(siguiente_hijo == actual) && !podar){
    
            evaluacion = Poda_AlfaBeta(siguiente_hijo,profundidad+1, last_c_piece,last_id_piece,last_dice,alpha,beta,heuristic);
            
             if (minimo > evaluacion){
                minimo = evaluacion;

                if (profundidad == 0){
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }
            }
            
            //minimo = min(minimo,evaluacion);
            
            beta = min(beta,evaluacion);
            if (beta <= alpha)
                podar = true;
            else
                siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece,last_dice);
        }
          
        //actualizamos
        return minimo;
    }

}

