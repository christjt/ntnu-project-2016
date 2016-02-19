//
// Created by christopher on 19.02.16.
//

#include "SelfAssemblyMechanisms/include/SelfAssemblyMechanismsUtilities.h"

double SelfAssemblyMechanismsUtilities::normalizeDouble(double x, double minFrom, double maxFrom, double minTo, double maxTo) {
    return ((x - minFrom)/(maxFrom - minFrom))*(maxTo - minTo) + minTo;
}