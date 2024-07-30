using System;
using System.IO;
using System.Diagnostics;
using System.Reflection;
using System.Net;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Compilation successful!");

        // Print environment information
        Console.WriteLine("Environment Information:");
        Console.WriteLine($"OS Version: {Environment.OSVersion}");
        Console.WriteLine($"64 Bit OS: {Environment.Is64BitOperatingSystem}");
        Console.WriteLine($"Machine Name: {Environment.MachineName}");
        Console.WriteLine($"User Name: {Environment.UserName}");
        Console.WriteLine($"Current Directory: {Environment.CurrentDirectory}");

        // Try to read sensitive files
        TryReadFile("/etc/passwd");
        TryReadFile("C:\\Windows\\win.ini");

        // List directory contents
        ListDirectoryContents(".");
        ListDirectoryContents("/");
        ListDirectoryContents("C:\\");

        // Try to execute a system command
        ExecuteCommand("whoami");
        ExecuteCommand("id");

        // Try to make an outbound network connection
        TryNetworkConnection("http://example.com");

        // Attempt to load and inspect assemblies
        InspectAssemblies();
    }

    static void TryReadFile(string path)
    {
        try
        {
            string content = File.ReadAllText(path);
            Console.WriteLine($"Contents of {path}:");
            Console.WriteLine(content);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error reading {path}: {ex.Message}");
        }
    }

    static void ListDirectoryContents(string path)
    {
        try
        {
            string[] files = Directory.GetFiles(path);
            string[] directories = Directory.GetDirectories(path);
            Console.WriteLine($"Contents of {path}:");
            foreach (var file in files)
            {
                Console.WriteLine($"File: {file}");
            }
            foreach (var dir in directories)
            {
                Console.WriteLine($"Directory: {dir}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error listing contents of {path}: {ex.Message}");
        }
    }

    static void ExecuteCommand(string command)
    {
        try
        {
            Process process = new Process();
            process.StartInfo.FileName = "/bin/bash";
            process.StartInfo.Arguments = $"-c \"{command}\"";
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.CreateNoWindow = true;
            process.Start();
            string output = process.StandardOutput.ReadToEnd();
            process.WaitForExit();
            Console.WriteLine($"Output of '{command}':");
            Console.WriteLine(output);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error executing '{command}': {ex.Message}");
        }
    }

    static void TryNetworkConnection(string url)
    {
        try
        {
            using (WebClient client = new WebClient())
            {
                string result = client.DownloadString(url);
                Console.WriteLine($"Successfully connected to {url}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error connecting to {url}: {ex.Message}");
        }
    }

    static void InspectAssemblies()
    {
        try
        {
            Assembly[] assemblies = AppDomain.CurrentDomain.GetAssemblies();
            Console.WriteLine("Loaded Assemblies:");
            foreach (var assembly in assemblies)
            {
                Console.WriteLine($"- {assembly.FullName}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error inspecting assemblies: {ex.Message}");
        }
    }
}
