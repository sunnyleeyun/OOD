// Implement a music playlist system. If the playlist is full (max: 100), the least-recent song will be removed from the playlist. Songs in the playlist can be played.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song
{
private:
    string title;
    string url;
    int timestamp;

public:
    Song(string title, string url) : title(title), url(url) {}

    void setTimestamp(int timestamp)
    {
        this->timestamp = timestamp;
    }

    int getTimestamp()
    {
        return this->timestamp;
    }
};

class MusicSystem
{
private:
    vector<Song> songs;
    int timestamp;

    void setTimestampForSong(Song song)
    {
        song.setTimestamp(this->timestamp);
        this->timestamp++;
    }

public:
    MusicSystem() : timestamp(0) {}

    // throw exceptions if failed
    void addSong(Song song)
    {
        if (songs.size() < 100)
        {
            setTimestampForSong(song);
            songs.push_back(song);
        }
        else
        {
            int minTimestamp = INT_MAX;
            int minTimestampIdx = 0;
            for (int i = 0, n = songs.size(); i < n; ++i)
            {
                int currTimestamp = songs[i].getTimestamp();
                if (currTimestamp < minTimestamp)
                {
                    minTimestamp = currTimestamp;
                    minTimestampIdx = i;
                }
            }
            songs[minTimestampIdx] = song;
        }
    }

    void listenSong(Song song)
    {
        setTimestampForSong(song);
    }
};

int main()
{
    MusicSystem musicSystem;
    Song song1("song1", "song1Url");
    musicSystem.addSong(song1);
    musicSystem.listenSong(song1);
    return 0;
}
