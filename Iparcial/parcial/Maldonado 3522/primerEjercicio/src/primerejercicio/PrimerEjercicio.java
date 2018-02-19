
package primerejercicio;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author mariandrea.maldonado
 */
public class PrimerEjercicio {

    
    public static void main(String[] args) throws FileNotFoundException, IOException {
          
      Scanner lector=new Scanner (new FileReader ("fuerte.txt"));
      FileWriter fichero = null;
      PrintWriter pw = null;
      fichero = new FileWriter("salidafuerte.txt");
      pw = new PrintWriter(fichero);

        while(lector.hasNext()){
            
           String linea = lector.nextLine();
           System.out.println(linea);
            
           String digitos[]= linea.split("");
           boolean cero=false;
           boolean derecha = true;
           int iterador = 0;
           int iteraciones=0;
           ArrayList<String> direcciones = new ArrayList<String>();
           
           while(!cero){
               
               int recorrido = Integer.parseInt("" + linea.charAt(iterador));
               int contador=1;
               System.out.println(recorrido);
               if(recorrido == 0) {
           
                  cero =true;
                   
               }else{
                   while(contador<=recorrido){
                   
                        if(derecha){
                            if(iterador == linea.length()) iterador=0;
                            iterador++;
                        }
                        else{
                            if(iterador == 0) iterador = linea.length();
                            iterador--;
                        }
                        contador++;
                     }
                    if(derecha) {
                        
                        derecha=false;
                        direcciones.add("0");
                    }else {
                        
                       derecha = true;
                        direcciones.add("1");
                    } 
                    iteraciones++;
                    
                }          
           }
         
           
           pw.println(iteraciones);
          
            for (int i = 0; i < direcciones.size(); i++) {
                
               pw.print(direcciones.get(i)+" ");
            }
            
            pw.println();
             
        }   
        fichero.close();
      
    }
    
}
