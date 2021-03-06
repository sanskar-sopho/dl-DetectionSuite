//
// Created by frivas on 5/02/17.
//

#include <iostream>
#include <string>
#include <Utils/SampleGenerationApp.h>
#include <DatasetConverters/readers/GenericDatasetReader.h>
#include <FrameworkEvaluator/DetectionsEvaluator.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <glog/logging.h>
#include <DatasetConverters/writers/GenericDatasetWriter.h>


class MyApp:public SampleGenerationApp{
public:
    MyApp(int argc, char* argv[]):SampleGenerationApp(argc,argv){
        this->requiredArguments.push_back("inputPath");
        this->requiredArguments.push_back("readerImplementation");
        this->requiredArguments.push_back("outputPath");
        this->requiredArguments.push_back("trainRatio");
        this->requiredArguments.push_back("readerNames");



    };
    void operator()(){
        Key inputPathKey=this->config->getKey("inputPath");
        Key outputPathKey=this->config->getKey("outputPath");
        Key readerImplementationKey = this->config->getKey("readerImplementation");
        Key writerImplementationKey = this->config->getKey("writerImplementation");
        Key trainRatioKey = this->config->getKey("trainRatio");
        Key readerNamesKey = this->config->getKey("readerNames");



        std::string trainPath=outputPathKey.getValue() + "/train";
        std::string testPath=outputPathKey.getValue() + "/test";


        GenericDatasetReaderPtr reader;
        if (inputPathKey.isVector()) {
            reader = GenericDatasetReaderPtr(
                    new GenericDatasetReader(inputPathKey.getValues(),readerNamesKey.getValue(), readerImplementationKey.getValue()));
        }
        else {
            reader = GenericDatasetReaderPtr(
                    new GenericDatasetReader(inputPathKey.getValue(),readerNamesKey.getValue(),
                                             readerImplementationKey.getValue()));
        }


        auto readerPtr = reader->getReader();

        std::vector<std::string> idsToFilter;
        idsToFilter.push_back("person");
        idsToFilter.push_back("person-falling");
        idsToFilter.push_back("person-fall");
        readerPtr->filterSamplesByID(idsToFilter);
        readerPtr->printDatasetStats();




        DatasetReaderPtr readerTest(new DatasetReader());
        DatasetReaderPtr readerTrain(new DatasetReader());


        int ratio=trainRatioKey.getValueAsInt();

        Sample sample;
        int counter=0;
        while (readerPtr->getNextSample(sample)){
            if (counter <ratio){
                readerTrain->addSample(sample);
            }
            else{
                readerTest->addSample(sample);
            }
            counter++;
            counter= counter % 10;
        }

        std::cout << "Train: " << std::endl;
        readerTrain->printDatasetStats();
        std::cout << "Test: " << std::endl;
        readerTest->printDatasetStats();


        GenericDatasetWriterPtr writerTest( new GenericDatasetWriter(testPath,readerTest,writerImplementationKey.getValue()));
        writerTest->getWriter()->process();

        GenericDatasetWriterPtr writerTrain( new GenericDatasetWriter(trainPath,readerTrain,writerImplementationKey.getValue()));
        writerTrain->getWriter()->process();

    };
};

int main (int argc, char* argv[]) {

    MyApp myApp(argc, argv);
    myApp.process();
}