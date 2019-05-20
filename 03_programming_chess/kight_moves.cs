using System;

class VideoSharp
{
    static int Main(string[] args)
    {
        VideoSharp program = new VideoSharp();
        Console.WriteLine("Hello {}\n", args.Length);
        ulong number = Int64.Parse(args[0]);
        Console.WriteLine(program.GetKnightMoves(number));
    }

    ulong GetKnightMoves(ulong knight)
    {
        ulong noGH = 0x3F3F3F3F3F3F3F3F;
        ulong noH = 0x7F7F7F7F7F7F7F7F;
        return noGH & (knight >> 10 | knight <<  6) |
                      (knight >> 17 | knight << 15) |
                      (knight >> 15 | knight << 17) |
                      (knight >>  6 | knight << 10);
    }
}