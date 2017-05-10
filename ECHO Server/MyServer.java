import java.io.*;
import java.net.*;

public class MyServer extends Thread
{
public ServerSocket serverSocket;

public MyServer(int port)throws IOException
{
serverSocket=new ServerSocket(port);
}

public void run()
{
while(true)
{
	try
	{
	String str=null;
	
	Socket socket=serverSocket.accept();
	System.out.println("Just connected"+socket.getRemoteSocketAddress());
	
	DataInputStream dis=new DataInputStream(socket.getInputStream());
	DataOutputStream dos=new DataOutputStream(socket.getOutputStream());

	BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	
	do
	{
	
	System.out.println("Client :"+dis.readUTF());
	System.out.println("server :");
	str=br.readLine();
	dos.writeUTF(str);

	}while(!str.equals("bye"));
	}
	
	catch(IOException e)
	{
	e.printStackTrace();
	}
	
	/*catch(Exception e)
	{
	e.printStackTrace();
	}*/
}
}


public static void main(String args[])throws IOException
{
Thread t=new MyServer(6543);
t.start();
}

}

