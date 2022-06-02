# include "AIPlayer.h"
# include "Parchis.h"
#include <limits.h>

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta


class MiHeuristica{
   private:
    Parchis estado;
     color my_color;
    
    static const int IS_EATING_MOVE = 120;
    static const int IS_GOAL_SCORE = 80;
    static const int DANGEROUS_SCORE = -20;
    static const int EATING_SCORE = 20;
    static const int WALL_SCORE = 20;
    static const int WALL_SCORE_AGAINST_ENEMY = 20;
    static const int SAFE_PIECE = 5;
    static const int FINAL_QUEUE = 15;


    
   public:  
    MiHeuristica(const Parchis &estado){
        this->estado = estado;
        this->my_color = estado.getCurrentColor();

    }
    /*******************************************************************/
    double positionScore(vector<Box> enemyPos, int &piece){
        Box miPieza = estado.getBoard().getPiece(my_color,piece);
        if (box_type::normal != miPieza.type)
            return 0;

        double score=0;

        for (int k=0; k< enemyPos.size() ; k++){
            bool tipoCasillaIgual = enemyPos[k].type == miPieza.type && miPieza.type == box_type::normal;
            if (tipoCasillaIgual ){
                score += eatingScore(miPieza, enemyPos[k]) + dangerousScore(miPieza, enemyPos[k]);
            }
        }


        return 0;
    }

    bool enPeligro(Box &miPieza, Box &enemy){
        return (miPieza.num - enemy.num > 0 && miPieza.num- enemy.num  <= 6  && !estado.isSafeBox(miPieza));
    }
    double eatingScore(Box &miPieza, Box &enemy){
        if  (enPeligro(miPieza, enemy))
            return EATING_SCORE; 
        return 0;
    }

    double dangerousScore(Box &miPieza, Box &enemy){
        if (enPeligro(enemy, miPieza)) 
            return DANGEROUS_SCORE;
        return 0;
    }

    /*******************************************************************/
    double isWall(int num_pieza, vector<Box> enemyPos){
        double score=0;
        Box miPieza = estado.getBoard().getPiece(my_color,num_pieza);
        if (estado.isWall(miPieza)){
            for (int k=0; k< enemyPos.size() ; k++){
                if (enPeligro(enemyPos[k], miPieza)) // si esta detras me conviene mantener el muro
                    score+=WALL_SCORE_AGAINST_ENEMY;
            }

            score+=WALL_SCORE;
        }

        return score;
    }
    /*******************************************************************/

    /*******************************************************************/

    double calculatePuntuacion(vector<color> & enemy_colors){
        double score = 0;
        vector<Box> enemyPos ;

        for (int i = 0; i < enemy_colors.size(); i++) {
            color c = enemy_colors[i];
            enemyPos = estado.getBoard().getPieces(c);
           
        }


        if (estado.isEatingMove() ){
            score+=IS_EATING_MOVE;
        } 

        if (estado.isGoalMove()){
            score+=IS_GOAL_SCORE;
        }


        for (int j = 0; j < num_pieces; j++){
           
           
            score += positionScore(enemyPos,j);
            // Valoro positivamente que la ficha esté en casilla segura o meta.
            
            
            score+= isWall(j,enemyPos);
           
            if (estado.isSafePiece(my_color, j)){
                score+= SAFE_PIECE;
            } 
            
            if (estado.getBoard().getPiece(my_color, j).type == box_type::final_queue){
                score += 40;
            } 
            
        } 



        return score;
    }

};

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
            valor = Poda_AlfaBeta(*actual, 0, c_piece, id_piece, dice, alpha, beta, ValoracionTest);

            cout<< "a"<< endl;

            break;
        case 1:
           valor = Poda_AlfaBeta(*actual, 0, c_piece, id_piece, dice, alpha, beta, miValoracion);
            break;
        case 2:
           // 
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
/*

   switch (id)
   {
        case 0:
            thinkAleatorio(c_piece,id_piece,dice);
            break;
        
        case 1:
            
            break;
        
        case 2:
            thinkFichaMasAdelantada(c_piece,id_piece,dice);
            break;
        
        case 3:
            thinkMejorOpcion(c_piece,id_piece,dice);
            break;
        

        default:
            break;
   }
*/

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



double AIPlayer::miValoracion(const Parchis &estado, int jugador){

    MiHeuristica miHeuristica(estado);
    int oponente = (jugador+1)%2;
    vector<color> ally = estado.getPlayerColors(jugador);
    vector<color> enemys = estado.getPlayerColors(oponente);
    

   


    return miHeuristica.calculatePuntuacion(enemys);
}


    

   /*

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
        return gana;
    else if (ganador == oponente)
        return pierde;
    else {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
       
        double puntuacion_my=0; 
      
        for (int i = 0; i < my_colors.size(); i++) {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++){
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isEatingMove()|| estado.isGoalMove()){
                    puntuacion_my+=120;
                } else if (estado.isWall(estado.getBoard().getPiece(c,j))){
                    puntuacion_my+=10;
                } else if (estado.isSafePiece(c, j)){
                    puntuacion_my+=5;
                } else if (estado.getBoard().getPiece(c, j).type == goal){
                    puntuacion_my += 40;
                }else if (estado.distanceToGoal(c,j) < 30){
                    puntuacion_my+=35;
                }

                puntuacion_my= -3*estado.piecesAtHome(c);
            }
         }
        // double puntuacion_op=0;
        // for (int i = 0; i < op_colors.size(); i++) {
        //     color c = op_colors[i];
        //     // Recorro las fichas de ese color.
        //     for (int j = 0; j < num_pieces; j++){
        //         // Valoro positivamente que la ficha esté en casilla segura o meta.
        //         if (estado.isEatingMove() || estado.isGoalMove()){
        //             puntuacion_op+=120;
        //         } else if (estado.isWall(estado.getBoard().getPiece(c,j))){
        //             puntuacion_op+=10;
        //         } else if (estado.isSafePiece(c, j)){
        //             puntuacion_op+=5;
        //         } else if (estado.getBoard().getPiece(c, j).type == goal){
        //             puntuacion_op += 40;
        //         } else if (estado.distanceToGoal(c,j) < 30){
        //             puntuacion_op+=35;
        //         }

        //         puntuacion_op = 2*estado.piecesAtGoal(c);
        //         puntuacion_op= -3*estado.piecesAtHome(c);


        //     }
        // }
        

        return puntuacion_my;*/
    



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


double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int profundidad, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const{
    
    if (profundidad == PROFUNDIDAD_ALFABETA || actual.gameOver()){
        return (ValoracionTest(actual, this->id));
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
            evaluacion = Poda_AlfaBeta(siguiente_hijo,profundidad+1, last_c_piece,last_id_piece,last_dice,alpha,beta,ValoracionTest);
            
            if (maximo < evaluacion){ // pensar si < o <= - primero o ultimo
                maximo = evaluacion;
                if (profundidad == 0){
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
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
            evaluacion = Poda_AlfaBeta(siguiente_hijo,profundidad+1, last_c_piece,last_id_piece,last_dice,alpha,beta,ValoracionTest);
            
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

