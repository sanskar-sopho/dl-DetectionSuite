//
// Created by frivas on 4/02/17.
//

#include <glog/logging.h>
#include "GenericLiveReader.h"


GenericLiveReader::GenericLiveReader(const std::string &path, const std::string& classNamesFile, const std::string &readerImplementation) {
    configureAvailablesImplementations(this->availableImplementations);
    if (std::find(this->availableImplementations.begin(), this->availableImplementations.end(), readerImplementation) != this->availableImplementations.end()){
        imp = getImplementation(readerImplementation);
        switch (imp) {
            case VIDEO:
                this->videoReaderPtr = VideoReaderPtr( new VideoReader(path));
                break;
//            case SPINELLO:
//                this->spinelloDatasetReaderPtr = SpinelloDatasetReaderPtr( new SpinelloDatasetReader(path,classNamesFile));
//                break;
//            case OWN:
//                this->ownDatasetReaderPtr = OwnDatasetReaderPtr( new OwnDatasetReader(path,classNamesFile));
//                break;
            default:
                LOG(WARNING)<<readerImplementation + " is not a valid reader implementation";
                break;
        }
    }
    else{
        LOG(WARNING)<<readerImplementation + " is not a valid reader implementation";
    }
}


GenericLiveReader::GenericLiveReader(const std::vector<std::string> &paths, const std::string& classNamesFile,
                                           const std::string &readerImplementation) {
    configureAvailablesImplementations(this->availableImplementations);
    if (std::find(this->availableImplementations.begin(), this->availableImplementations.end(), readerImplementation) != this->availableImplementations.end()){
        imp = getImplementation(readerImplementation);
        switch (imp) {
//            case YOLO:
//                this->yoloDatasetReaderPtr = YoloDatasetReaderPtr( new YoloDatasetReader());
//                for (auto it =paths.begin(), end= paths.end(); it != end; ++it){
//                    int idx = std::distance(paths.begin(),it);
//                    std::stringstream ss;
//                    ss << idx << "_";
//                    this->yoloDatasetReaderPtr->appendDataset(*it,ss.str());
//                }
//                break;
//            case SPINELLO:
//                this->spinelloDatasetReaderPtr = SpinelloDatasetReaderPtr( new SpinelloDatasetReader());
//                for (auto it =paths.begin(), end= paths.end(); it != end; ++it){
//                    int idx = std::distance(paths.begin(),it);
//                    std::stringstream ss;
//                    ss << idx << "_";
//                    this->spinelloDatasetReaderPtr->appendDataset(*it,ss.str());
//                }
//                break;
//            case OWN:
//                this->ownDatasetReaderPtr = OwnDatasetReaderPtr( new OwnDatasetReader());
//                for (auto it =paths.begin(), end= paths.end(); it != end; ++it){
//                    int idx = std::distance(paths.begin(),it);
//                    std::stringstream ss;
//                    ss << idx << "_";
//                    this->ownDatasetReaderPtr->appendDataset(*it,ss.str());
//                }
//                break;
            default:
                LOG(WARNING)<< readerImplementation + " is not a valid reader implementation";
                break;
        }
    }
    else{
        LOG(WARNING) << readerImplementation + " is not a valid reader implementation";
    }


}


void GenericLiveReader::configureAvailablesImplementations(std::vector<std::string>& data) {
    data.push_back("recorder");
    data.push_back("jderobot");
    data.push_back("video");
}

LIVEREADER_IMPLEMENTATIONS GenericLiveReader::getImplementation(const std::string& readerImplementation) {
//    if (readerImplementation.compare("yolo")==0){
//        return YOLO;
//    }
//    if (readerImplementation.compare("spinello")==0){
//        return SPINELLO;
//    }
//    if (readerImplementation.compare("own")==0){
//        return OWN;
//    }
    if (readerImplementation.compare("video")==0){
        return VIDEO;
    }
}

DatasetReaderPtr GenericLiveReader::getReader() {
    switch (imp) {
//        case YOLO:
//            return this->yoloDatasetReaderPtr;
//        case SPINELLO:
//            return this->spinelloDatasetReaderPtr;
        case VIDEO:
            return this->videoReaderPtr;
        default:
            LOG(WARNING)<<imp + " is not a valid reader implementation";
            break;
    }
}

std::vector<std::string> GenericLiveReader::getAvailableImplementations() {
    std::vector<std::string> data;

    configureAvailablesImplementations(data);
    return data;
}

