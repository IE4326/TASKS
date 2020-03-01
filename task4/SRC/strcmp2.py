# -*- coding: utf-8 -*-
import sys

def rexcomp(str1, str2):
    #checkstring и checkstrlen хранят проверочную подстроку и её длину соответственно
    checkstring = ''
    checkstrlen = 0
    c = 0
    #переменная first хранит состояние до первого сравнения подстроки с str1
    first = True
    #посимвольно собираем проверочную подстроку до символа * или конца строки.
    #когда встречается * или конец проверяем вхождение подстроки
    #если есть совпадение - продолжаем цикл и собираем следующую подстроку или возвращаем true
    for i in str2:
        c += 1

        #если мы дошли до конца и текущий символ *
        if (i == '*' and c == len(str2)):
            if (checkstrlen == 0):
                return True
            else:
                if (first):
                    if (checkstring == str1[:checkstrlen]):
                        return True
                    else:
                        return False
                else:
                    if (checkstring in str1):
                        return True
                    else:
                        return False

        #если символ не звёздочка и не конец строки добавляем символ в подстроку и продолжаем цикл
        elif (i != '*' and c != len(str2)):
            checkstring = checkstring + i
            checkstrlen += 1
            continue

        #если мы дошли до конца и символ не звёздочка - добавляем его в подстроку на месте
        #и проверяем совпадение
        elif (c == len(str2) and i != '*'):
            checkstring = checkstring + i
            checkstrlen += 1
            if first:
                if (checkstring == str1):
                    return True
                else:
                    return False
            elif (not first and checkstrlen < c):
                while (str1[:checkstrlen] != checkstring):
                    str1 = str1[1:]
                    if (str1 == ''):
                        return False
                if (checkstring == str1):
                    return True
                else:
                    continue
            else:
                if (checkstring == str1):
                    return True
                else:
                    return False

        #при всех остальных условиях выполняется следующая часть цикла
        if first:
            first = False
            if checkstrlen == 0:
                continue
            else:
                if (str1[:checkstrlen] == checkstring):
                    str1 = str1[checkstrlen:]
                    checkstring = ''
                    checkstrlen = 0
                    continue
                else:
                    return False

        else:
            if checkstrlen == 0:
                continue
            else:
                if checkstring in str1:
                    #если совпадение есть - слайсим из str1 всё до подстроки включительно
                    while(str1[:checkstrlen] != checkstring):
                        str1 = str1[1:]
                    str1 = str1[checkstrlen:]
                    checkstring = ''
                    checkstrlen = 0
                    continue
                else:
                    return False

    #когда во второй строке не осталось символов и мы покинули цикл
    #если в str1 что то осталось строки не совпадают
    if (len(str1) > 0):
        return False
    else:
        return True

# Запуск программы начинается здесь
if (len(sys.argv) != 3):
    print('Usage: strcmp.py <str1> <str2>')
    sys.exit(1)
if ('*' in sys.argv[1]):
    print('* symbol is not allowed in first string!')
    sys.exit(1)
if (rexcomp(sys.argv[1], sys.argv[2])):
    print('OK')
else:
    print('KO')
