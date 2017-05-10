import java.io.*;
import java.net.*;

public class EchoMyClient {

	public static void main(String [] infi) {


	try {

		String str = null;
		
		Socket socket = new Socket("localhost",6543);

		System.out.println("Just connected to "+socket.getRemoteSocketAddress());

DataInputStream dis = new DataInputStream(socket.getInputStream());
DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
BufferedReader buff = new BufferedReader(new InputStreamReader(System.in));


		do {

				System.out.println("Client : ");
				str = buff.readLine();
				dos.writeUTF(str);
				System.out.println("Server : "+dis.readUTF());

			}while(!str.equals("bye"));

           socket.close();

		}

		catch(Exception e){

							e.printStackTrace();
						  }
		}
}