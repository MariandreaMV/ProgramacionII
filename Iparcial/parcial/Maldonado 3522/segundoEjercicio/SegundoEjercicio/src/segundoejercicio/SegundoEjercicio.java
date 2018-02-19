
package segundoejercicio;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 *
 * @author mariandrea.maldonado
 */
public class SegundoEjercicio {

   
    public static void main(String[] args) throws FileNotFoundException, IOException {
        
       Scanner lector=new Scanner (new FileReader ("excusas.in.txt"));
       FileWriter fichero = null;
       PrintWriter pw = null;
       fichero = new FileWriter("salida.txt");
       pw = new PrintWriter(fichero);
       int n=1;
       
       
        while(lector.hasNext()){
            
           String linea = lector.nextLine();
           String numeros[] = linea.split(" ");
           
           int palabras= Integer.parseInt(""+numeros[0]);
           int excusas = Integer.parseInt(""+numeros[1]);
           ArrayList<String> ListaPalabras = new ArrayList<String>();
           ArrayList<String> listaExcusas = new ArrayList<String>();
           
            for (int i = 0; i < palabras; i++) {
                
                ListaPalabras.add(lector.nextLine());
            }
            for (int i = 0; i < excusas; i++) {
                
                listaExcusas.add(lector.nextLine());
            }
            
            int MejorExcusa=0;
            int posicion=0;
            
            for (int i = 0; i < listaExcusas.size(); i++) {
                
                StringTokenizer st = new StringTokenizer(listaExcusas.get(i), " .,?!");
                
                ArrayList<String> ExcusasSeparadas = new ArrayList<String>();
                
                while(st.hasMoreTokens()) {
                    
                    String p=st.nextToken();
                    ExcusasSeparadas .add(p);
                   // System.out.println(p);
                }
                
                
                for (int j = 0; j < ListaPalabras.size(); j++) {
                    
                    int cantidadPalabras=0;
                    
                    for (int k = 0; k < ExcusasSeparadas.size(); k++) {
                        System.out.println(ListaPalabras.get(j)+" "+ExcusasSeparadas.get(k));
                        if (ListaPalabras.get(j).equalsIgnoreCase(ExcusasSeparadas.get(k))) {
                            cantidadPalabras++;
                        }
                    }
                    
                    if(cantidadPalabras>MejorExcusa){
                         MejorExcusa= cantidadPalabras;
                         posicion = i;
                    }
                }
  
            }
            System.out.println("Excusas#"+n);
            System.out.println(listaExcusas.get(posicion));
            pw.println("Excene#"+ n);
            pw.println(listaExcusas.get(posicion)+" ");
            n++;
        
        }
            fichero.close();
    }
    
}
