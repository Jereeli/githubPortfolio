"""
Ohjelma alkaa soittamaan haluttua musiikkitiedostoa kun saavun kotiin.
"""
from os import environ
environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "1"
import pygame, sys, time, subprocess, os, platform
from datetime import datetime
import pyttsx3


song = 'Taustamusiikki.mp3'

pygame.mixer.init() # Ala vastaanottamaan ääntä

pygame.mixer.music.load(song) # Siirrä musiikkitiedosto projektiin

def tervehdys():
    engine = pyttsx3.init()
    engine.say(f"Welcome home, now playing {song}")
    engine.runAndWait()

def ping(ip):
    """
    Tarkistaa onko tutkittava laite samassa verkossa tietokoneen kanssa
    :param ip: IPhonen IP
    :return: Bool
    """
    tulos = subprocess.run(["arp", "-a"], capture_output=True, text=True)
    if ip in tulos.stdout:
        return True
    else:
        return False

import threading

def kuuntele_käyttäjän_syöte():
    while True:
        pysäytä = input(f"Keskeytä musiikki painamalla Enter\n")
        if pygame.mixer.music.get_busy():
            pygame.mixer.music.pause()
            print("Musiikki pausella.")
            jatka = input("Jatka musiikkia painamalla Enter\n")
            pygame.mixer.music.unpause()
            print("Musiikki jatkuu.\n")

def lepotila():
    """
    Jotta ohjelman ei tarvitsisi edelleen joka minuutti tarkistaa paljonko kello on,
    tehdään funktio "lepotila" joka pistää ohjelman suorituksen lepotilaan yön ajaksi.
    :return:
    """

    lippu = True
    while lippu:
        nykyinen_tunti = datetime.now().hour
        if nykyinen_tunti == 11 or nykyinen_tunti == 12:
            lippu = False
            break
        else:
            time.sleep(10000)
    return

def tarkista_aika(aika):
    """
    Antaa luvan suorittaa ohjelma jos kello on vähemmän kuin 11 illalla
    :param aika: tämän hetkinen tunti
    :return: Bool
    """
    if 11 <= aika < 23:
        return True
    else:
        return False

def main():

    threading.Thread(target=kuuntele_käyttäjän_syöte, daemon=True).start()
    running = True


    while running: # Aloittaa ohjelman ajon ja pitää sen käynnissä

        nykyinen_tunti = datetime.now().hour
        aika = tarkista_aika(nykyinen_tunti) # Tarkistetaan että ei ole yö


        if aika:
            subprocess.run(["ping","-n", "1", "192.168.100.11"])
            aika = tarkista_aika(nykyinen_tunti) # Tallennetaan joka loopin alussa sen hetkinen aika
            käynnistä = ping("192.168.100.11") # Annetaan arvo True, jos tietokone tunnistaa kännykäni IP osoitteen samassa wifissä
            if not käynnistä:
                print("Lähdit kotoa. Hei hei!")
                pygame.mixer.music.stop()  # Kun kännykkää ei enään tunnisteta samassa wifissä, lopetetaan musiikin soitto

            elif pygame.mixer.music.get_busy(): # Jos musiikki soi jo, ei tehdä mitään
                pass

            elif käynnistä: # Jos musiikkia ei vielä soiteta, aloitetaan sen soitto
                print(f"\nTervetuloa kotiin! Soitetaan musiikkia :)")
                tervehdys() # Samalla kun aloitetaan musiikki, tervehditään t2s:llä
                pygame.mixer.music.play(loops=0, start=0, fade_ms=2000)


            time.sleep(60)
        else:
            print("Hiljennetään musiikki koska kello on liian paljon")
            lepotila()



if __name__ == "__main__":
    main()