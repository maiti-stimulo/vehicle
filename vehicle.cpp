//Maiti MASTER ROBOTICS
//Referenciar un punt definit al pla utilitzant diferents punts de referència
//Hem creat un directori build,i un CMakeLists.txt per a poder compilar i veure les diferents posicions del punt definit respecte tres punts diferents.
// Hem d'aplicar la rotació i translació de vectors.


// llibreries necessaries per poder fer els càlculs.
#include <iostream>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Dense>
#include <cmath>
using namespace Eigen;
using namespace std;

int main()
{
    // Declarem les variables que defineixen les matrius i els vectors
    Eigen::Vector3d QB, Q0, Q0_1;
    Eigen::Vector3d MB;
    Eigen::Matrix3d T_s_b;
    Eigen::Matrix3d T_b_0;
    Eigen::Matrix3d T_s_0;

    // definim la localitzacio del punt P0 respecte origen i l'angle respecte el pla X
    double Alfa_deg=30;
    Eigen:: Vector3d P0(50,25,1);
    

    // definim la calibracio del punt MB, respecte el punt P0 del vehicle (centre eix posterior)
    double Beta_deg=25;
    MB <<1.5, 0.75, 1;
    	
    // defimin la mesura de QS, es a dir la distància entre el punt MB i el punt Q
    Eigen:: Vector3d QS(12, 5, 1);
        
    // conversio de angles a radians
    double Alfa=M_PI/180*Alfa_deg;
    double Beta=M_PI/180*Beta_deg;
    
    //Dades matriu de rotacio i translacio de S respecte B
    T_s_b << cos(Beta),-sin(Beta),MB(0),sin(Beta),cos(Beta),MB(1),0,0,MB(2);
    	
    //multipliquem el resultat de la matriu per la distància al punt QS, i ens donarà la distància 	del punt QB
    QB =T_s_b * QS;
    cout <<"distància cotxe al objecte QB:\n"<< QB << std::endl;
    
    
    //Dades matriu de rotacio i translacio de b respecte 0
    T_b_0 << cos(Alfa),-sin(Alfa),P0(0),sin(Alfa),cos(Alfa),P0(1),0,0,P0(2);
    
    //multipliquem el resultat de la matriu per la distància al punt QB, i ens donarà la distància 	del punt Q0
    Q0 = T_b_0 * QB;
    cout << "distancia objecte al centre coord Q0:\n" <<Q0 << std::endl;

    //Comprovem que les operacions anteriors son correctes, multipliquem la T_b_0 per la T_s_b, sempre per aquest ordre, ja que les matrius no compleixen la propietat comuntativa, això ens donarà una T_S_0, que al multiplicar-la per la distància QS en ha de donar el mateixos resultats que Q0.
    T_s_0=T_b_0*T_s_b;
    Q0_1=T_s_0*QS;
    cout << "comprovacio distància Q0:\n" <<Q0_1 << std::endl;

    return 0;
    
    
}
