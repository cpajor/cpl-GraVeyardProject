ffmpeg -i work/CLICK.WAV -acodec pcm_s16le -ac 2 -ar 44100 -map_metadata -1 work/CLICK2.WAV
pause