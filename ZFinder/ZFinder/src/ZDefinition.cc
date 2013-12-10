#include "ZFinder/ZFinder/interface/ZDefinition.h"

// Standard Libraries
#include <algorithm>  // std::swap


namespace zf {
    ZDefinition::ZDefinition(
            const std::string NAME,
            const std::vector<std::string>& CUTS0,
            const std::vector<std::string>& CUTS1,
            const double MZ_MIN, const double MZ_MAX
            )
        : MZ_MIN_(MZ_MIN), MZ_MAX_(MZ_MAX), NAME_(NAME) {
            /*
             * Save the cut values, and check that they are sane.
             */
            if (CUTS0.size() != CUTS1.size()) {
                throw "In ZDefinition, CUTS0 and CUTS1 have different length!";
            }

            if (MZ_MIN_ > MZ_MAX_) {
                throw "In ZDefinition, MZ_MIN > MZ_MAX!";
            }
            std::vector<std::string> cuts[2];
            cuts[0] = std::vector<std::string>(CUTS0);
            cuts[1] = std::vector<std::string>(CUTS1);

            // Fill in our cutinfo_ vector
            InitVariables(cuts[0].size());

            // Loop over all cut stages and file an object with relevant info.
            for (int i_cutset = 0; i_cutset < 2; ++i_cutset) {
                const std::vector<std::string>* CUT_VEC = &cuts[i_cutset];
                for (unsigned int i_cut = 0; i_cut < CUT_VEC->size(); ++i_cut) {
                    CutInfo* cutinfo = &cutinfo_[i_cutset].at(i_cut);
                    cutinfo->cut = CUT_VEC->at(i_cut);

                    // We use a ! flag in the [0] slot to invert the cut
                    if (cutinfo->cut[0] == '!') {
                        cutinfo->invert = true;
                        cutinfo->cut.erase(0, 1);
                    } else {
                        cutinfo->invert = false;
                    }

                    // If there is an =, >, < in the string we use it to cut on a value
                    // from the ZElectron, otherwise we assume it is a cut and pass it
                    // through. We also pull out the variable being compared.
                    cutinfo->comp_type = GetComparisonType(&cutinfo->cut);
                    cutinfo->comp_var = GetComparisonVariable(&cutinfo->cut);
                    if (cutinfo->comp_type != CT_NONE) {  // Is a comparison
                        cutinfo->comp_val = GetComparisonValue(&cutinfo->cut);
                    } else {
                        cutinfo->comp_val = -1;
                    }
                }
            }
        }

    void ZDefinition::InitVariables(const unsigned int SIZE) {
        /*
         * We fill in cutinfo_ with default values, as well as pass_
         */
        for (int j = 0; j < 2; ++j) {
            for (unsigned int i = 0; i < SIZE; ++i) {
                // Initialize cutinfo_
                CutInfo ci;
                ci.cut = "";
                ci.invert = false;
                ci.comp_type = CT_NONE;
                ci.comp_var = CV_NONE;
                ci.comp_val = -1;
                cutinfo_[j].push_back(ci);
                // Initialize pass_
                pass_[j][0].push_back(false);
                pass_[j][1].push_back(false);
            }
        }
    }

    void ZDefinition::ApplySelection(ZFinderEvent* zf_event) {
        /*
         * Given a ZFinderEvent, apply all steps of the selection to it. We
         * loop over the each cut stage, then each set of cuts, then each
         * electron and determine which combinations pass.
         */
        if (zf_event->reco_z.m > MZ_MAX_ || zf_event->reco_z.m < MZ_MIN_) {
            zf_event->AddZDef(NAME_, false);
            return;
        }

        for (int i_cutset = 0; i_cutset < 2; ++i_cutset) {
            std::vector<CutInfo>* cutinfo_vec = &cutinfo_[i_cutset];
            for (int i_elec = 0; i_elec < 2; ++i_elec) {
                for (unsigned int i_cutinfo = 0; i_cutinfo < cutinfo_vec->size(); ++i_cutinfo) {
                    CutInfo* cutinfo = &(cutinfo_vec->at(i_cutinfo));
                    if (cutinfo->comp_type != CT_NONE) {
                        pass_[i_cutset][i_elec][i_cutinfo] = ComparisonCut(*cutinfo, i_elec, zf_event);
                    } else {
                        pass_[i_cutset][i_elec][i_cutinfo] = NormalCut(*cutinfo, i_elec, zf_event);
                    }
                }
            }
        }

        /*
         * We now check for the electron pairing that passed the most cuts.
         * We check e0 with cuts0 and e1 with cuts1, and if they fail we try e1
         * with cuts0 and e0 with cuts1.
         */
        // e0 && cut0 case
        bool pass_0011 = true;
        bool pass_0110 = true;
        std::vector<bool>::const_iterator i_pass;
        for (i_pass = pass_[0][0].begin(); i_pass != pass_[0][0].end(); ++i_pass) {
            pass_0011 = (*i_pass) && pass_0011;
            if (!pass_0011) { break; }
        }
        if (pass_0011) {
            for (i_pass = pass_[1][1].begin(); i_pass != pass_[1][1].end(); ++i_pass) {
                pass_0011 = (*i_pass) && pass_0011;
                if (!pass_0011) { break; }
            }
        }
        if (pass_0011) {
            zf_event->AddZDef(NAME_, true);
        }
        // e1 && cut0 case
        else {
            for (i_pass = pass_[0][1].begin(); i_pass != pass_[0][1].end(); ++i_pass) {
                pass_0110 = (*i_pass) && pass_0110;
                if (!pass_0110) { break; }
            }
            if (pass_0110) {
                for (i_pass = pass_[1][0].begin(); i_pass != pass_[1][0].end(); ++i_pass) {
                    pass_0110 = (*i_pass) && pass_0110;
                    if (!pass_0110) { break; }
                }
            }
        }
        if (pass_0110) {
            zf_event->AddZDef(NAME_, true);
        }
        // Failed both sets
        else {
            zf_event->AddZDef(NAME_, false);
        }
    }

    bool ZDefinition::NormalCut(const CutInfo& CUTINFO, const int I_ELEC, ZFinderEvent* zf_event) {
        // Read internal variables
        const bool INVERT = CUTINFO.invert;
        const std::string CUT = CUTINFO.cut;

        // Check the cut on the event
        bool passed = false;
        if (I_ELEC == 0) {
            passed = zf_event->e0->CutPassed(CUT);
        } else {
            passed = zf_event->e1->CutPassed(CUT);
        }

        if (INVERT) {
            return !passed;
        } else {
            return passed;
        }
    }

    bool ZDefinition::ComparisonCut(const CutInfo& CUTINFO, const int I_ELEC, ZFinderEvent* zf_event) {
        // Read internal variables
        const bool INVERT = CUTINFO.invert;
        const std::string CUT = CUTINFO.cut;
        const ComparisonType COMP_TYPE = CUTINFO.comp_type;
        const ComparisonVariable COMP_VAR = CUTINFO.comp_var;
        const double COMP_VAL = CUTINFO.comp_val;

        // Check if the cut is on a generator quantity
        bool use_truth;
        if (   COMP_VAR == CV_GPT
                || COMP_VAR == CV_GETA
                || COMP_VAR == CV_GPHI
                || COMP_VAR == CV_GCHARGE
           ) {
            use_truth = true;
        } else {
            use_truth = false;
        }

        // Get the electron we want
        ZFinderElectron* zf_elec;
        if (I_ELEC == 0) {
            if (use_truth) {
                zf_elec = zf_event->e0_truth;
            } else {
                zf_elec = zf_event->e0;
            }
        } else {
            if (use_truth) {
                zf_elec = zf_event->e1_truth;
            } else {
                zf_elec = zf_event->e1;
            }
        }

        // Pull the value from the electron
        double e_val = -1;
        switch(COMP_VAR) {
            case CV_PT:
            case CV_GPT:
                e_val = zf_elec->pt;
                break;
            case CV_ETA:
            case CV_GETA:
                e_val = zf_elec->eta;
                break;
            case CV_PHI:
            case CV_GPHI:
                e_val = zf_elec->phi;
                break;
            case CV_CHARGE:
            case CV_GCHARGE:
                e_val = zf_elec->charge;
                break;
                // Cases where it makes no sense to continue
            case CV_NONE:
            default:
                return false;
        }

        // Check the cut
        bool passed = false;
        switch(COMP_TYPE) {
            case CT_EQUAL:
                passed = (e_val == COMP_VAL);
                break;
            case CT_GT:
                passed = (e_val > COMP_VAL);
                break;
            case CT_LT:
                passed = (e_val < COMP_VAL);
                break;
            case CT_GTE:
                passed = (e_val >= COMP_VAL);
                break;
            case CT_LTE:
                passed = (e_val <= COMP_VAL);
                break;
                // Cases where it makes no sense to continue
            case CT_NONE:
            default:
                return false;
        }

        // Return result with invert if needed
        if (INVERT) {
            return !passed;
        } else {
            return passed;
        }
    }

    ZDefinition::ComparisonType ZDefinition::GetComparisonType(const std::string* cut) {
        /*
         * Determine what type of comparison the cut string is requesting. Can be one of:
         * <, >, =, <=, >=
         */
        using std::string;
        // Less Than
        if (cut->find("<") != string::npos) {
            if (cut->find("=") != string::npos) {
                return CT_LTE;
            } else {
                return CT_LT;
            }
        }
        // Greater Than
        else if (cut->find(">") != string::npos) {
            if (cut->find("=") != string::npos) {
                return CT_GTE;
            } else {
                return CT_GT;
            }
        }
        // Just Equal
        else if (cut->find("=") != string::npos) {
            return CT_EQUAL;
        }
        // None of the above
        return CT_NONE;
    }

    ZDefinition::ComparisonVariable ZDefinition::GetComparisonVariable(const std::string* cut) {
        /*
         * Determine what variable for comparison the cut string is requesting.
         * We just check all possibilities.
         */
        using std::string;
        if (cut->compare(0, 2, "pt")) {
            return CV_PT;
        }
        else if (cut->compare(0, 3, "gpt")) {
            return CV_GPT;
        }
        else if (cut->compare(0, 3, "eta")) {
            return CV_ETA;
        }
        else if (cut->compare(0, 4, "geta")) {
            return CV_GETA;
        }
        else if (cut->compare(0, 3, "phi")) {
            return CV_PHI;
        }
        else if (cut->compare(0, 4, "gphi")) {
            return CV_GPHI;
        }
        else if (cut->compare(0, 6, "charge")) {
            return CV_CHARGE;
        }
        else if (cut->compare(0, 7, "gcharge")) {
            return CV_GCHARGE;
        }
        return CV_NONE;
    }

    double ZDefinition::GetComparisonValue(const std::string* cut) {
        /*
         * Convert everything after the operator in the cut string to a double
         */
        int gt_pos = cut->find(">");
        int lt_pos = cut->find("<");
        int eq_pos = cut->find("=");
        int pos;

        // Find the largest
        if (gt_pos > lt_pos && gt_pos > eq_pos) {
            pos = gt_pos;
        } else if (lt_pos > gt_pos && lt_pos > eq_pos) {
            pos = gt_pos;
        } else {
            pos = eq_pos;
        }

        // Get the end of the string starting after the operator and convert it
        // to a double
        std::string ds = cut->substr(pos+1);
        std::istringstream iss(ds);
        double x;
        iss >> x;
        return x;
    }
}  // namespace zf