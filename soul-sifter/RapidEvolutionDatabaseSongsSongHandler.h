//
//  RapidEvolutionDatabaseSongsSongHandler.h
//  soul-sifter
//
//  Created by Robby Neale on 11/5/12.
//
//

#ifndef __soul_sifter__RapidEvolutionDatabaseSongsSongHandler__
#define __soul_sifter__RapidEvolutionDatabaseSongsSongHandler__

#include "RapidEvolutionDatabaseAbstractHandler.h"

#include <string>

#include <boost/any.hpp>

#include "RESong.h"

class RapidEvolutionDatabaseSongsSongHandler : public RapidEvolutionDatabaseAbstractHandler {
public:
    RapidEvolutionDatabaseSongsSongHandler(xercesc::SAX2XMLReader* parser,
                                           RapidEvolutionDatabaseAbstractHandler* parentHandler);
    
    const XMLCh* const getQname() {
        return qname;
    }
    
    void startElement(const XMLCh* const uri,
                      const XMLCh* const localname,
                      const XMLCh* const qname,
                      const xercesc::Attributes& attrs);
    
    void endElement(const XMLCh* const uri,
                    const XMLCh* const localName,
                    const XMLCh* const qName);
    
    void characters(const XMLCh* const chars, const XMLSize_t length);
private:
    const XMLCh* const qname;
    RESong song;
    
    boost::any fieldPointer;
    
    // attributes
    const XMLCh* const unique_id_elem;
    const XMLCh* const songid_winfo_elem;
    const XMLCh* const songid_elem;
    const XMLCh* const shortid_elem;
    const XMLCh* const shortid_winfo_elem;
    const XMLCh* const artist_elem;
    const XMLCh* const album_elem;
    const XMLCh* const track_elem;
    const XMLCh* const title_elem;
    const XMLCh* const time_elem;
    const XMLCh* const time_signature_elem;
    const XMLCh* const filename_elem;
    const XMLCh* const digital_only_elem;
    const XMLCh* const compilation_elem;
    const XMLCh* const key_start_elem;
    const XMLCh* const key_accuracy_elem;
    const XMLCh* const bpm_start_elem;
    const XMLCh* const bpm_accuracy_elem;
    const XMLCh* const rating_elem;
    const XMLCh* const date_added_elem;
    const XMLCh* const catalog_id_elem;
    const XMLCh* const label_elem;
    const XMLCh* const remix_elem;
    const XMLCh* const num_plays_elem;
    const XMLCh* const comments_elem;
    const XMLCh* const release_date_elem;
    const XMLCh* const featuring_elem;
    const XMLCh* const key_end_elem;
    const XMLCh* const disabled_elem;
    const XMLCh* const bpm_end_elem;
    const XMLCh* const beat_intensity_elem;
    const XMLCh* const replay_gain_elem;
    const XMLCh* const album_cover_elem;
    const XMLCh* const styles_bitmask_elem;
};

#endif /* defined(__soul_sifter__RapidEvolutionDatabaseSongsSongHandler__) */
