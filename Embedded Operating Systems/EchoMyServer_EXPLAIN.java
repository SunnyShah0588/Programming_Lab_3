import java.io.*;
import java.net.*;

public class EchoMyServer extends Thread {  //A thread is a thread of execution in a program. 
                                           //The Java Virtual Machine allows an application 
                                          //to have multiple threads of execution running concurrently.

public ServerSocket serverSocket; /*This class implements server sockets. A server socket waits
 								for requests to come in over the network. It performs some operation
 									 based on that request, and then possibly returns a result
 									  to the requester.*/

public EchoMyServer(int port)throws IOException
{
serverSocket=new ServerSocket(port); /*Constructor and Description :ServerSocket(int port)
Creates a server socket, bound to the specified port*/
}

///*This subclass should override the run method of class Thread.*/
public void run() 
{   
while(true)
{
	try
	{
	String str=null;
	
	Socket socket=serverSocket.accept();
	System.out.println("Just connected -->"+socket.getRemoteSocketAddress());
	
	DataInputStream dis = new DataInputStream(socket.getInputStream());
	DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
	do
	{
	
	System.out.println("Client :  "+dis.readUTF());  /*The java.io.DataInputStream.readUTF()
	                                method reads in a string that has been encoded using a modified 
	                                UTF-8 format. The string of character is decoded from the
	                                 UTF and returned as String.*/
	System.out.println("server :");
	str = br.readLine();
	dos.writeUTF(str);

	}while(!str.equals("bye"));
	}
	
	catch(IOException e)
	{
	e.printStackTrace();
	}
	
}
}


public static void main(String args[])throws IOException
{
Thread t = new EchoMyServer(6543);
t.start();
}

}

