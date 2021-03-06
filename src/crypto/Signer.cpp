/*
 * libdigidocpp
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "Signer.h"

#include "Conf.h"
#include "log.h"
#include "crypto/Digest.h"
#include "crypto/X509Crypto.h"
#include "crypto/X509Cert.h"

using namespace digidoc;
using namespace std;

namespace digidoc
{
class SignerPrivate
{
public:
    string city, stateOrProvince, postalCode, countryName, method;
    vector<string> signerRoles;
};
}

/**
 * @class digidoc::Signer
 * @brief <code>Signer</code> interface. Provides interface for signing documents.
 * 
 * Digidoc LIB implements PKCS11, PKCS12, CNG
 * signer class that allows signing with EstId chip card. Other implementations may provide signing
 * implementation with other public-key cryptography systems.
 */

/**
 * Constructor
 */
Signer::Signer()
    : d(new SignerPrivate)
{
    d->method = CONF(signatureDigestUri);
}

/**
 * Destructor
 */
Signer::~Signer()
{
    delete d;
}

/**
 * Sets signature production place according XAdES standard. Note that setting the signature production place is optional.
 * @param city
 * @param stateOrProvince
 * @param postalCode
 * @param countryName
 */
void Signer::setSignatureProductionPlace(const string &city,
    const string &stateOrProvince, const string &postalCode, const string &countryName)
{
    d->city = city;
    d->stateOrProvince = stateOrProvince;
    d->postalCode = postalCode;
    d->countryName = countryName;
}

/**
 * @fn digidoc::Signer::cert
 *
 * Returns signer certificate. Must be reimplemented when subclassing
 */

/**
 * Returns city from signature production place
 */
string Signer::city() const
{
    return d->city;
}

/**
 * Returns state from signature production place
 */
string Signer::stateOrProvince() const
{
    return d->stateOrProvince;
}

/**
 * Returns postal code from signature production place
 */
string Signer::postalCode() const
{
    return d->postalCode;
}

/**
 * Returns country from signature production place
 */
string Signer::countryName() const
{
    return d->countryName;
}

/**
 * Sets signature roles according XAdES standard. The parameter may contain the signer’s role and optionally the signer’s resolution. Note that only one  signer role value (i.e. one &lt;ClaimedRole&gt; XML element) should be used. 
 * If the signer role contains both role and resolution then they must be separated with a slash mark, e.g. “role / resolution”. 
 */
void Signer::setSignerRoles(const vector<string> &signerRoles)
{
    d->signerRoles = signerRoles;
}

/**
 * @fn void digidoc::Signer::sign(const std::string &method, const std::vector<unsigned char> &digest, std::vector<unsigned char> &signature)
 *
 * Signs message digest. Must be reimplemented when subclassing
 * @param method digest method to be used
 * @param digest digest to sign
 * @param signature signed result
 * @throws Exception throws exception on error 
 * @deprecated Remove on next API change
 */

/**
 * Signs message digest. Must be reimplemented when subclassing
 * @param method digest method to be used
 * @param digest digest to sign
 * @returns signed result
 * @throws Exception throws exception on error
 */
vector<unsigned char> Signer::sign(const string &method, const vector<unsigned char> &digest)
{
    vector<unsigned char> sig;
    sign(method, digest, sig);
    return sig;
}

/**
 * Returns signer roles
 */
vector<string> Signer::signerRoles() const
{
    return d->signerRoles;
}

/**
 * Sets signature method
 */
void Signer::setMethod(const string &method)
{
    d->method = method;
}

/**
 * Gets signature method
 */
string Signer::method() const
{
    // Estoniand ID-Card specific hack for older cards, they support only max SHA224
    X509Cert c = cert();
    if(d->method != URI_SHA1 && d->method != URI_SHA224 &&
        X509Crypto(c).rsaModulus().size() <= 128)
    {
        for(const string &pol: c.certificatePolicies())
        {
            if(pol.compare(0, 22, "1.3.6.1.4.1.10015.1.1.") == 0 ||
                pol.compare(0, 22, "1.3.6.1.4.1.10015.3.1.") == 0)
                 return URI_SHA224;
        }
    }
    return d->method;
}
