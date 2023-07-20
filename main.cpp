
#include <iostream>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
    // usage -media <url> -tune <tune> -play -dl

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " -f <folder> -url <url> -tune <tune> -play -dl" << std::endl;
        return 0;
    }

    // parse arguments

    bool play = false;
    bool dl = false;
    std::string url;
    int nbofsemitons = 999;
    std::string folderpath;
    std::string foldername;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-url") == 0)
        {
            url = argv[i + 1];
        }
        else if (strcmp(argv[i], "-tune") == 0)
        {
            nbofsemitons = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-play") == 0)
        {
            play = true;
        }
        else if (strcmp(argv[i], "-dl") == 0)
        {
            dl = true;
        }else if (strcmp(argv[i], "-f") == 0)
        {
            // create if not exist
            folderpath = argv[i + 1];

            // get last part of folder name
            foldername = folderpath.substr(folderpath.find_last_of("/\\") + 1);
        }
    }

    // use gstreamer to play the media from url

    if (play)
    {
        std::string cmd = "gst-launch-1.0 playbin uri=" + url;
        system(cmd.c_str());

    } else if (dl)
    {
        // we want to download the video and audio from the url

        // download the video and audio and save to folder ./tmp
        std::string cmd = "yt-dlp -f bestvideo[ext=mp4]+bestaudio[ext=m4a]/mp4 " + url+ " -o ./tmp/video.mp4 --verbose";;
        system(cmd.c_str());

    }
    if(nbofsemitons != 999){
        double value = pow(2,nbofsemitons/12.);
        std:: string cmd = "ffmpeg -i "+folderpath+"/0.mp4 -filter_complex \"[0:a]rubberband=pitch="+std::to_string(value)+"[a]\" -map \"[a]\" -map 0:v -c:v copy "+folderpath+"/"+foldername+"_"+std::to_string(nbofsemitons)+".mp4";
        std::cout << cmd << std::endl;
        system(cmd.c_str());
    }

}