//
// Created by frivas on 5/02/17.
//

#include <glog/logging.h>
#include "GenericDatasetWriter.h"


GenericDatasetWriter::GenericDatasetWriter(const std::string &path,DatasetReaderPtr &reader, const std::string &writerImplementation) {
    configureAvailableImplementations(this->availableImplementations);
    if (std::find(this->availableImplementations.begin(), this->availableImplementations.end(), writerImplementation) != this->availableImplementations.end()){
        imp = getImplementation(writerImplementation);
        switch (imp) {
            case WR_YOLO:
                this->yoloDatasetWriterPtr = YoloDatasetWriterPtr( new YoloDatasetWriter(path,reader));
                break;
            case WR_OWN:
                this->ownDatasetWriterPtr = OwnDatasetWriterPtr( new OwnDatasetWriter(path,reader));
                break;
            default:
                LOG(WARNING)<<writerImplementation + " is not a valid writer implementation";
                break;
        }
    }
    else{
        LOG(WARNING)<<writerImplementation + " is not a valid writer implementation";
    }
}



void GenericDatasetWriter::configureAvailableImplementations(std::vector<std::string> &data) {
    data.push_back("own");
    data.push_back("yolo");
}

WRITER_IMPLEMENTATIONS GenericDatasetWriter::getImplementation(const std::string &writerImplementation) {
    if (writerImplementation.compare("yolo")==0){
        return WR_YOLO;
    }
    if (writerImplementation.compare("own")==0){
        return WR_OWN;
    }
}

DatasetWriterPtr GenericDatasetWriter::getWriter() {
    switch (imp) {
        case WR_YOLO:
            return this->yoloDatasetWriterPtr;
        case WR_OWN:
            return this->ownDatasetWriterPtr;
        default:
            break;
    }
}

std::vector<std::string> GenericDatasetWriter::getAvailableImplementations() {
    std::vector<std::string> data;
    configureAvailableImplementations(data);
    return data;
}



