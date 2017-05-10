import java.io.*;
import java.net.*;

public class MyClient
{
public static void main(String args[])
{
try
{
String str=null;
Socket socket=new Socket("localhost",6543);

System.out.println("Just connected"+socket.getRemoteSocketAddress());

DataInputStream dis=new DataInputStream(socket.getInputStream());
DataOutputStream dos=new DataOutputStream(socket.getOutputStream());

BufferedReader br=new BufferedReader(new InputStreamReader(System.in));

do
{
System.out.println("Client :");
str=br.readLine();
dos.writeUTF(str);
System.out.println("Server :"+dis.readUTF());

}while(!str.equals("bye"));



}
catch(Exception e)
{
e.printStackTrace();
}
}
}

