import os
allowed = ['-','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9']
positiveFile = "PositiveSentimentWords.txt"
negativeFile = "NegativeSentimentWords.txt"
# fileToAnalyze = "TestFile.txt"
fileToAnalyze = "thehoundofthebaskervilles(1).txt"
def purifyWord(word):
    pureWord=word.lower()
    for char in pureWord:
        if(char not in allowed):
            pureWord.replace(char,'')
    return pureWord
def main():
    # Set up dictionary for words
    words={}
    positiveCount = 0
    negativeCount = 0
    neutralCount =0

    f = open(positiveFile)
    content = f.read().split('\n')
    f.close()
    for word in content:
        words[word.lower()]=1

    f = open(negativeFile)
    content = f.read().split('\n')
    f.close()
    for word in content:
        words[word.lower()]=-1
    #Read File and Analyze it
    

    f = open(fileToAnalyze)
    content = f.read().split('. ')
    for sentence in content:
        sentenceWords=sentence.split(' ')
        if(len(sentenceWords)>0):
            sumTotal = 0
            for word in sentenceWords:
                word =  purifyWord(word)
                if(len(word)>1 and word in words.keys()):
                    sumTotal += words[word]

            if(sumTotal > 0):
                positiveCount += 1
            elif(sumTotal < 0):
                negativeCount += 1
            else:
                neutralCount += 1
    # Final Output Counts
    print("Postive:  %d"%positiveCount)
    print("Negative: %d"%negativeCount)
    print("Neutral:  %d"%neutralCount)
    
if __name__ == "__main__":
    main()