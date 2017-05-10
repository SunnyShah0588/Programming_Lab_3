import java.io.*;
import java.net.*;

public class EchoMyServer extends Thread {

	public ServerSocket serverSocket;

		public EchoMyServer(int port) throws IOException {

			serverSocket = new ServerSocket(port);
		}

			public void run() {

					while(true) {
	
									try{

										String str=null;
										
										Socket socket = serverSocket.accept();
										System.out.println("Just connected to --->"+socket.getRemoteSocketAddress());
										
										DataInputStream  dis  = new DataInputStream(socket.getInputStream());
										DataOutputStream dos  = new DataOutputStream(socket.getOutputStream());
										BufferedReader   buff   = new BufferedReader(new InputStreamReader(System.in));
										 
										do
										{
										
										System.out.println("Client : "+dis.readUTF());
										System.out.println("server :");
										str=buff.readLine();
										dos.writeUTF(str);

										}while(!str.equals("bye"));
										
										}catch(IOException e){

																e.printStackTrace();
															 }
										
								}
							}


	public static void main(String [] args) throws IOException {

			Thread t = new EchoMyServer(6543);
			t.start();
	}

}

