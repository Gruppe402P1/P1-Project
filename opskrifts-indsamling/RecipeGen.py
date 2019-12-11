from selenium import webdriver
from bs4 import BeautifulSoup
import pandas as pd
import time

def scrape_opskrift(scrape_url, f):
    driver.get(scrape_url);
    time.sleep(1.5);
    
    dish_name = driver.find_element_by_xpath('//*[@id="AutoNumber4"]/tbody/tr/td[1]/b/font/font').text.replace(" ","_");
    dish_name = dedansihfy(dish_name);

    people_count = int(driver.find_element_by_xpath('//*[@id="AutoNumber6"]/tbody/tr[1]/td[2]/font').text)
    dish_people = people_count if people_count != 0 else 1;
    
    difficulty = "[SKRIV]";
    
    read_time = int((driver.find_element_by_xpath('//*[@id="AutoNumber6"]/tbody/tr[3]/td[2]/font').text).split(" ")[0]);
    dish_time = read_time if int(read_time) > 0 else "[SKRIV]";
    
    main_text = driver.find_element_by_id('AutoNumber8').text;
    main_text = dedansihfy(main_text);
    main_text_modified = divide_all_numbs_in_string(main_text, dish_people);
    
    dish_guide =  main_text_modified.split("Ingredienser:")[0].replace("Fremgangsmåde:\n", "");
    dish_guide = dish_guide[:-1]; #Removes last char
    
    dish_ingredients = main_text_modified.split("Ingredienser:")[1];


    print("@");
    f.write("@" + "\n")
    print(dish_name);
    f.write(dish_name + "\n")
    print(difficulty);
    f.write(difficulty + "\n")
    print(str(dish_time));
    f.write(str(dish_time) + "\n");
    print_opskrifter(dish_ingredients, f);
    print(dish_guide);
    f.write(dish_guide + "\n")
    f.write("Opskrift fra " + scrape_url + ", Besoegt 9. december 2019\n");

def scrape_opskrift_links(scrape_url):
    driver.get(scrape_url);
    time.sleep(1.5);
    link_list = driver.find_elements_by_id("AutoNumber2");
    print("-----OPSKRIFTER-----");
    recipe_url_list = [];
    for item in link_list:
        if link_list[0] != item:
            print(item.text);
            print(item.find_element_by_xpath('.//tbody/tr/td[2]/font/a').get_attribute("href"));
            recipe_url_list.append(item.find_element_by_xpath('.//tbody/tr/td[2]/font/a').get_attribute("href"));
    
    return recipe_url_list;

def divide_all_numbs_in_string(in_str, divide_int):
    numbers_in_string = [int(s) for s in in_str.split() if s.isdigit()];
    rest_str = in_str;
    out_str = "";
    for number in numbers_in_string:
        split_str = rest_str.split(str(number), 1);
        out_str += split_str[0] + ("0" if number == 0 else str(('%f' % (number / divide_int)).rstrip('0').rstrip('.'))); #Avoid divide by zero
        rest_str = split_str[1];
        print(out_str);
    
    return out_str + rest_str;

def print_opskrifter(in_str, out_file):
    ingredient_list = in_str.split("\n");
    del ingredient_list[0];
    for ingredient_line in ingredient_list:
        if(len(ingredient_line.split()) < 3):
            print(ingredient_line, end=' ');
            out_file.write(ingredient_line + " ");
            print("[SKRIV]");
            out_file.write("[SKRIV]\n");
        elif(ingredient_line.split()[0].replace(".", "1").replace(",","1").isdigit()):
            print((ingredient_line.split(" ", 2)[2]).replace(" ", "_"), end=' ');
            out_file.write((ingredient_line.split(" ", 2)[2]).replace(" ", "_") + " ");
            print("[SKRIV]", end=' ');
            out_file.write("[SKRIV]" + " ")
            print(ingredient_line.split()[0].replace(",","."), end=' ');
            out_file.write(ingredient_line.split()[0].replace(",",".") + " ");
            print(ingredient_line.split()[1]);
            out_file.write(ingredient_line.split()[1] + "\n")
        else:
            print(ingredient_line, end=' ');
            out_file.write(ingredient_line + " ");
            print("[SKRIV]");
            out_file.write("[SKRIV]" + "\n");
    
    print("#")
    out_file.write("#" + "\n");

def dedansihfy (in_str):
    return in_str.replace("@", "").replace("æ", "ae").replace("Æ", "Ae").replace("ø", "oe").replace("Ø", "Oe").replace("å", "aa").replace("Å", "Aa");


print("Start");
f = open("recipe.txt","w+");
driver = webdriver.Chrome("C:\Shitty_scripts\chromedriver");
menu_url_list = ['http://www.net-opskrifter.dk/list.asp?sort=Hovedretter',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=2',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=3',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=4',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=5',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=6',
                 'http://www.net-opskrifter.dk/list.asp?sort=Hovedretter&page=7',
                 'http://www.net-opskrifter.dk/list.asp?sort=Pasta&page=1',
                 'http://www.net-opskrifter.dk/list.asp?sort=Pasta&page=2',
                 'http://www.net-opskrifter.dk/list.asp?sort=Fedtfattigt&page=1',
                 'http://www.net-opskrifter.dk/list.asp?sort=Fedtfattigt&page=2',
                 'http://www.net-opskrifter.dk/list.asp?sort=Fedtfattigt&page=3',
                 'http://www.net-opskrifter.dk/list.asp?sort=Vegetarmad',
                 'http://www.net-opskrifter.dk/list.asp?sort=Vegetarmad&page=2'];

for menu_url in menu_url_list:
    recipe_url_list = scrape_opskrift_links(menu_url);

    for url in recipe_url_list:
        scrape_opskrift(url, f);
    
f.close();
driver.quit();