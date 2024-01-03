// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



/*
   ___    ____    ____    ___   ____    ___      _      _   _ 
  / _ \  | __ )  / ___|  |_ _| |  _ \  |_ _|    / \    | \ | |
 | | | | |  _ \  \___ \   | |  | | | |  | |    / _ \   |  \| |
 | |_| | | |_) |  ___) |  | |  | |_| |  | |   / ___ \  | |\  |
  \___/  |____/  |____/  |___| |____/  |___| /_/   \_\ |_| \_|
*/                                                              


#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "E.Dinham 040817 D L Y S M";
    const CScript genesisOutputScript = CScript() << ParseHex("048ea926fca81ed93cfe04ec79ca91df7011ebecbc28017505bc0a329c073fd667a73eeed3fe81af4c3d6b86f19bbd39f46bfef1f0baed25d0d6a2ca55e6bf21a3") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
 /*  
  __  __     _     ___  _   _  _   _  _____  _____ 
 |  \/  |   / \   |_ _|| \ | || \ | || ____||_   _|
 | |\/| |  / _ \   | | |  \| ||  \| ||  _|    | |  
 | |  | | / ___ \  | | | |\  || |\  || |___   | |  
 |_|  |_|/_/   \_\|___||_| \_||_| \_||_____|  |_|  
*/
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 1800;
        consensus.BIP34Height = 1800;
        consensus.BIP34Hash = uint256S("0xe80f878b0e8876be960e2ca555a62988bf5bd6b5e5a67f8461ce4d719dccff1c");
        consensus.BIP65Height = 1800;
        consensus.BIP66Height = 1800;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 7 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 1.2 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180;
        consensus.nMinerConfirmationWindow = 240;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1700673000;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1700773000;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1700673000;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1700773000;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000005564e004882456e");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa1061f96ca2cad4568ebaff4f526904ebd45520a9e0d6c0af061923fdb54b722");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0xd2;

        nDefaultPort = 2333;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlock(1700476087, 2084885399, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x119eb27cd47508416221a987205c1838288298d966c126d3b27643b16bc839c7"));
        assert(genesis.hashMerkleRoot == uint256S("0xb3e759d55ce7c2d760917562e866d908096b1c090a0704d4372a52385ddd8fa2"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
       
        vSeeds.emplace_back("dnsseeds.obsidiancoin.org");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,115);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,163);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "obn";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {  0, uint256S("0x119eb27cd47508416221a987205c1838288298d966c126d3b27643b16bc839c7")},
                {  1, uint256S("0x6c74d01c657edaac06d88aebdbe8f6dd37720cd333b67272ae4754ad05240be0")},
                {  16, uint256S("0x40ee070ab49c3503ea396af1895005c6636b4d6851900f57b03dfefe951014bf")},
                { 42, uint256S("0x08f94b8a81959139bda5e6afbef09227a4682acc1e8a1dfb146e3bda50c05142")},
                { 500, uint256S("0x601237c6c090b8bffad2defad4157227ae670370880a63285e1b1e33e1b20c45")},
                { 1014, uint256S("0x7f64546aacd66828a4db84cc48ce4e7e7cb6595125168894c91fdb4ed8f6d920")},
                { 1680, uint256S("0xebea1c2db842321d38095d3f534730c9f6ebb9f91ab6bbeb85c3034825abba81")}, // Softfork CSV and Segwit activation started
                { 1761, uint256S("0x03fe4130eece27280c1f7c492e6769bed9f847bd20ba169e8ecd8b45edcc3f2e")},
                { 1800, uint256S("0xe80f878b0e8876be960e2ca555a62988bf5bd6b5e5a67f8461ce4d719dccff1c")}, // BIPs 16, 34, 65 and 66 activated
                { 2160, uint256S("0xfd34917be33e79ad6d80cbdf494d15c8f4e3a1d182ea14f5f0dd0bd9cf4c22dc")}, // Softfork CSV and Segwit status locked_in
                { 2400, uint256S("0xa33f33d5f6770da72262f5855ac1761555d183b80b76724e21567a3ec2a86b17")}, // Softfork CSV and Segwit activated
                { 2415, uint256S("0x92ff2434f6a10fa3e42cd8cee22e38a7cb6c06440bfbac72267bba6c8173ddd8")},
                { 9528, uint256S("0xedeae39bfb42d5b644428de1052c549b40024b9888bcf9e6cfb0dcd0cfac4a44")},
                { 12224, uint256S("0xb5996ce08731440249caa06e7cf9e9a04028a547d9ef434491a0c7fa0bd0ded7")},
                { 28031, uint256S("0x48f75ff9740595f81caa9f759565a45c0166bdfb891a02dced2d093e117ca4ab")},
                { 55256, uint256S("0x5d6a349985df19c40352a87a12fde3955c77036182adf5cac96b7a50e9f52e11")},
                { 83892, uint256S("0x56346ec538145357f158a4ebf6aa73d0d254ddb81863f744c374c934ee52664f")},
                { 118408, uint256S("0xbebc9d7669a3223d39cb6c149fb2ab0c0111b33cedf55af22d5daffbb350a9fc")},
                { 143569, uint256S("0xa1061f96ca2cad4568ebaff4f526904ebd45520a9e0d6c0af061923fdb54b722")},         
      
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 143569
            /* nTime    */ 1704284733,
            /* nTxCount */ 160529,
            /* dTxRate  */ 0.0422582076
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Testnet (v3)
 */

 /*
   _____  _____  ____  _____  _   _  _____  _____ 
 |_   _|| ____|/ ___||_   _|| \ | || ____||_   _|
   | |  |  _|  \___ \  | |  |  \| ||  _|    | |  
   | |  | |___  ___) | | |  | |\  || |___   | |  
   |_|  |_____||____/  |_|  |_| \_||_____|  |_|  
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on testnet
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x753b2b9821eae9be141e0f6d624e5cbeddf18412dc591fbf053fbae75a8ef1ad");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = -1;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = -1;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x753b2b9821eae9be141e0f6d624e5cbeddf18412dc591fbf053fbae75a8ef1ad");

        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xd1;
        nDefaultPort = 12333;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 2;
        m_assumed_chain_state_size = 1;

        genesis = CreateGenesisBlock(1700476105, 385805302, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x753b2b9821eae9be141e0f6d624e5cbeddf18412dc591fbf053fbae75a8ef1ad"));
        assert(genesis.hashMerkleRoot == uint256S("0xb3e759d55ce7c2d760917562e866d908096b1c090a0704d4372a52385ddd8fa2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.emplace_back("00.00.00.00");


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,96);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,223);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tobn";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0x753b2b9821eae9be141e0f6d624e5cbeddf18412dc591fbf053fbae75a8ef1ad")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 e79561972208ba3a02c308482176b33f3ec841d4213ea7bbaa3f22b7c8a16f32
            /* nTime    */ 1700476105,
            /* nTxCount */ 0,
            /* dTxRate  */ 0.00
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
 
 /*
   ____   _____  ____  _____  _____  ____  _____ 
 |  _ \ | ____|/ ___||_   _|| ____|/ ___||_   _|
 | |_) ||  _| | |  _   | |  |  _|  \___ \  | |  
 |  _ < | |___| |_| |  | |  | |___  ___) | | |  
 |_| \_\|_____|\____|  |_|  |_____||____/  |_|  
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 500; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in functional tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xb8;
        pchMessageStart[1] = 0xb9;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xb1;
        nDefaultPort = 22333;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateVersionBitsParametersFromArgs(args);

        genesis = CreateGenesisBlock(1296688602, 0, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x00"));
        //assert(genesis.hashMerkleRoot == uint256S("0x00"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = {
            {
                {0, uint256S("0x00")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,123);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,188);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "robn";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateVersionBitsParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateVersionBitsParametersFromArgs(const ArgsManager& args)
{
    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
